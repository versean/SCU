/* 
 * File:        engrl_2_1_C.ino
 * Description: An LED goes on. The LED will stay on until a button is pressed. A half second after the button is pressed, the LED will go off and an alternate color LED will go on for 5 seconds. After this the whole cycle repeats. 
 * Created:     2026-02-12
 * Author:      Sean Cajigal
 */

const int buttonPin = 2;
const int led1Pin = 12;
const int led2Pin = 10;

int buttonState=0;

void setup()
{
  // set led pin to OUTPUT mode and button pin to INPUT
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin,LOW);

  if (buttonState == HIGH) { // if button pressed, turn LED on for 3 seconds, else LED off
    delay(500);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    delay(5000);
    digitalWrite(led2Pin, LOW);
  }
}
