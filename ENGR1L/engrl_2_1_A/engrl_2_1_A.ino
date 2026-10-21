/* 
 * File:        engrl_2_1_A.ino
 * Description: A program that turns on an LED for 3 seconds every time a button is pressed.
 * Created:     2026-02-12
 * Author:      Sean Cajigal
 */

const int buttonPin = 2;
const int ledPin = 12;

int buttonState=0;

void setup()
{
  // set led pin to OUTPUT mode and button pin to INPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // update button state
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == HIGH) { // if button pressed, turn LED on for 3 seconds, else LED off
    digitalWrite(ledPin,HIGH);
    delay(3000);
    digitalWrite(ledPin,LOW);
  } else {
    digitalWrite(ledPin,LOW);
  }
}
