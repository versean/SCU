/* 
 * File:        engrl_2_1_D.ino
 * Description: Flashes an LED. On a button press,
                the LED turns on for 2 seconds.
                After this the whole cycle repeats.
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

  // flash LED
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);

  if (buttonState == HIGH) { // if button pressed, turn LED on for 2 seconds
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
  }
}
