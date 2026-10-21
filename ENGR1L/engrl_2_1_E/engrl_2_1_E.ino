/* 
 * File:        engrl_2_1_E.ino
 * Description: Lights an LED. The LED should turn off after
                a button has been pushed 3 times. Assume
                there is at least 1/4 second between button 
                presses.
 * Created:     2026-02-12
 * Author:      Sean Cajigal
 */

const int buttonPin = 2;
const int ledPin = 12;

int buttonState=0;
int buttonPresses=0;

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

  // check if the button's been pressed 3 times
  if (buttonPresses >= 3) {
    buttonPresses = 0;
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }

  if (buttonState == HIGH) { // if button pressed, increment buttonPresses
    delay(250);
    buttonPresses+=1;
  }
}
