/* 
 * File:        activity3.ino
 * Description: A program that activates a piezoelectric speaker
 * Created:     2026-02-11
 * Author:      Sean Cajigal
 */
   
int piezoPin=3; // sets pin

void setup() {
  pinMode(piezoPin,OUTPUT); // sets pin for output voltage
  
  tone(piezoPin, 200);
  delay(1500);
  noTone(piezoPin);
  tone(piezoPin, 400);
}

void loop() {
  // nothing to be looped
}
