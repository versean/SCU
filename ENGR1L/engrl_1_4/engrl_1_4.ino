/* 
 * File:        activity4.ino
 * Description: A program that repeatedly blinks an LED, before sounding off a piezo speaker.
 * Created:     2026-02-11
 * Author:      Sean Cajigal
 */

// set working pins
int ledPin = 2;
int piezoPin = 3;

void setup() {
  // sets pins to output voltage
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  for (int i = 0; i < 10; i++) { // blinks LED 10 times
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  // sets off piezo speaker
  tone(piezoPin, 8000);
  delay(500);
  noTone(piezoPin);
}

void loop() {
  // nothing to be looped
}
