/* 
 * File:        activity2.ino
 * Description: A program that flashes an LED
 * Created:     2026-02-11
 * Author:      Sean Cajigal
 */

int ledPin1 = 3; // sets which pin

void setup()
{
  pinMode(ledPin1, OUTPUT); // set pin for output
  
  digitalWrite(ledPin1, HIGH);
  delay(5000);
  digitalWrite(ledPin1, LOW);
  delay(3000);
  for (int i = 0; i < 10; i++) { // loop 10 times
    digitalWrite(ledPin1, LOW);
    delay(500);
    digitalWrite(ledPin1, HIGH);
    delay(500);
  }
  digitalWrite(ledPin1, LOW);
}

void loop() 
{
  // nothing needs to be looped
}
