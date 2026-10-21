/* 
 * File:        engrl_2_1_B.ino
 * Description: Flashes an LED 10 times at a rate of 2 Hz every time a button is pressed. When the button is not pressed, the LED should be off.
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
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == HIGH) { // if button pressed, turn LED on for 3 seconds, else LED off
    
    for (int i = 0; i < 10; i++) { // flash LED 10 times
      digitalWrite(ledPin,HIGH);
      delay(250);
      digitalWrite(ledPin,LOW);
      delay(250);
    }
    
  } else {
    digitalWrite(ledPin,LOW);
  }
}
