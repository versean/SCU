/* 
 * File:		activity1.ino
 * Description:	A program that flashes LEDs at different frequencies.
 * Created:		2026-02-11
 * Author:		Sean Cajigal
 */

int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int leddelay = 20; // global delay

void setup()
{
  // Sets Arduino pins 1 thru 3 to output power.
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() // LED 3 Loop, for every LED 3 blink, LED 2 blinks twice, and LED 3 blinks four times
{
  digitalWrite(ledPin3, HIGH);
  for (int i = 0; i < 2; i++) { // LED 2 Loop, for every LED 2 blink, LED 1 blinks twice
    digitalWrite(ledPin2, HIGH);
    for (int j = 0; j < 2; j++) { // LED 1 Loop
      digitalWrite(ledPin1, HIGH);
      delay(leddelay);
      digitalWrite(ledPin1, LOW);
      delay(leddelay);
    }
    digitalWrite(ledPin2, LOW);
    for (int j = 0; j < 2; j++) { // LED 1 Loop
      digitalWrite(ledPin1, HIGH);
      delay(leddelay);
      digitalWrite(ledPin1, LOW);
      delay(leddelay);
    }
  }
  digitalWrite(ledPin3, LOW);
  for (int i = 0; i < 2; i++) { // LED 2 Loop, for every LED 2 blink, LED 1 blinks twice
    digitalWrite(ledPin2, HIGH);
    for (int j = 0; j < 2; j++) { // LED 1 Loop
      digitalWrite(ledPin1, HIGH);
      delay(leddelay);
      digitalWrite(ledPin1, LOW);
      delay(leddelay);
    }
    digitalWrite(ledPin2, LOW);
    for (int j = 0; j < 2; j++) { // LED 1 Loop
      digitalWrite(ledPin1, HIGH);
      delay(leddelay);
      digitalWrite(ledPin1, LOW);
      delay(leddelay);
    }
  }
}
