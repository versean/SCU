/* ServoTest with Arduino
   Author: Sean Cajigal
   Date: 2/19/26 */

#include <Servo.h> // include the Servo library

Servo myservo; //create the servo object
int pos=0; //variable to store the servo position
int knobState = 0;

int knobPin = A0;

void setup()
{
  myservo.attach(3); // attaches the servo on pin 3 to a servo object
  pinMode(knobPin, INPUT); // sets the knob pin to receive input
}

void loop()
{
  //every 10ms, update the knob state and write to the servo motor
  knobState = analogRead(knobPin);
  myservo.write(knobState/8);
  delay(10);
}
