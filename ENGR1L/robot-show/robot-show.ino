/* 
 * robot-show.ino
 * Sean Cajigal & Sidd Menon 2026
 */

// Pin Assignments
const int buttonPin = 3;
const int piezoPin = 9;
const int soundSensorPin = A0;
const int servoPin = 10;

// For servo control
#include <Servo.h>
Servo myServo;

// Flags
bool waitingForButton = true;
bool waitingForSound = false;
bool isRunning = false;

// Timer variables
unsigned long startTime;
const unsigned long runDuration = 60000; // 2 minutes

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(soundSensorPin, INPUT);
 
  myServo.attach(servoPin);
  myServo.write(90); // Ensure servo is stopped at start

  // Initialize serial communication for debugging output
  Serial.begin(9600);
  Serial.println("\n--- Arduino Uno Melody Player ---");
  
  // Set the buzzer pin as an output.
  pinMode(piezoPin, OUTPUT);
}

// check if done, which is one of the following conditions
// (1) boat has run for 2 minutes
// (2) button pressed early 
void checkIfDone() {
  if (isRunning) {
    if (millis() - startTime >= runDuration || digitalRead(buttonPin) == LOW) {
      stopRobot();
      waitingForButton = true; // Reset so you can press the button again
    }
  }
}

void loop() {
  // STEP 1: Wait for the physical button press
  if (waitingForButton) {
    if (digitalRead(buttonPin) == HIGH) { // Button pressed pulls pin to GND
      delay(50); // Simple debounce
      playPulse();
      waitingForButton = false;
      waitingForSound = true;
    }
  }

  // STEP 2: Wait for the sound sensor to hear the piezo
  if (waitingForSound) {
    if (analogRead(soundSensorPin) > 400) {
      activateRobot();
      waitingForSound = false;
    }
  }

  // STEP 3: Handle the 2-minute timer
  checkIfDone();
}

// piezo speaker beep sound
void playPulse() {
  digitalWrite(piezoPin, HIGH);
  delay(200);
  digitalWrite(piezoPin, LOW);
}

// records start time in milliseconds, begins motor and melody
void activateRobot() {
  isRunning = true;
  startTime = millis();
  myServo.write(135); // Rotate clockwise
  playMelody();
}

void stopRobot() {
  isRunning = false;
  myServo.write(90); // Stop
}

// The following code was written by Vihanga Nethmaka. 
// The melody playing alongside the boat animation would not be possible without him.
// * Some code has been modified to be able to work synchronously with the boat code above.

// Uno_Melody_Player.ino
// ----------------------------------------------------------------------
// Plays the melody data using the standard Arduino tone() function.
// Designed for Arduino Uno R3, which requires careful memory management.
// ----------------------------------------------------------------------

// *** IMPORTANT WARNING FOR ARDUINO UNO R3 ***
// The Uno has limited Flash (32KB) and RAM (2KB). If your MIDI file 
// is very long or complex, the generated C array may exceed the Uno's 
// storage capacity, resulting in compilation errors or unexpected behavior.
// If this happens, try a shorter MIDI file or switch to an ESP32 or Mega board.
// ***

// Required for the PROGMEM functions (accessing data from Flash memory)
#include <avr/pgmspace.h> 

// Includes the generated data files
#include "pitches.h"
#include "melody_data.h" 

// --- Melody Play Function ---
void playMelody() {
  // Iterate through the notes in the melody_data array.
  for (int thisNote = 0; thisNote < melody_length; thisNote++) {
    
    // Read pitch and duration from Flash memory (PROGMEM).
    // This is crucial for the Uno to save valuable RAM.
    int pitch = pgm_read_word_near(melody + thisNote);
    int noteDuration = pgm_read_word_near(durations + thisNote);
    
    // Check if the pitch is a rest (REST is defined as 0 in pitches.h).
    if (pitch != REST) {
      // Plays a tone at the specified pitch for the noteDuration time.
      tone(piezoPin, pitch, noteDuration);
    } else {
      // Stop the tone for a REST.
      noTone(piezoPin); 
    }

    // Pause for the exact duration of the note/rest.
    delay(noteDuration);

    // Stop the tone explicitly to ensure a clean break before the next note/pause.
    noTone(piezoPin); 

    // Pause for a small interval before the next note starts.
    // This pause provides a necessary staccato effect.
    #ifdef PAUSE_BETWEEN_NOTES_MS
      delay(PAUSE_BETWEEN_NOTES_MS);
    #else
      delay(20); // Default pause if macro not found (20ms)
    #endif

    // This code below was added in by Sean Cajigal and not part of
    // Vihanga Nethmaka's original code. This code is needed for
    // checking if done (another is needed beyond the one in the
    // loop because playMelody doesn't run asynchronously due to
    // Arduino Uno's being single-cored)
    checkIfDone();
    if (isRunning == false) {
      break;
    }
  }
}