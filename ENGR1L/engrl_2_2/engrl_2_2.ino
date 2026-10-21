/* 
 * File:        engrl_2_2.ino
 * Description: Turns LED on then light is shown on the photoresistor
 * Created:     2026-02-12
 * Author:      Sean Cajigal
 */

const int photoPin = A0;
const int led1Pin = 12;

int lightState=0;

void setup()
{
  // set led pin to OUTPUT mode and photoresistor to INPUT
  pinMode(led1Pin, OUTPUT);
  pinMode(photoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // update lightState
  lightState = analogRead(photoPin);
  Serial.println(lightState);

  // if light shown on photoresistor is greater than 20, the LED is on, else off
  if (lightState > 20) {
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }
}
