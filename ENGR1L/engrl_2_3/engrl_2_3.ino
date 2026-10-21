/* 
 * File:        engrl_2_3.ino
 * Description: 3 knobs control an RGB led
 * Created:     2026-02-12
 * Author:      Sean Cajigal
 */

const int ledR = 9;
const int ledG = 10;
const int ledB = 11;

const int knobR = A0;
const int knobG = A1;
const int knobB = A2;

int knobRState=0;
int knobGState=0;
int knobBState=0;

void setup()
{
  // set LED components to OUTPUT
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  // set knobs to INPUT
  pinMode(knobR, INPUT);
  pinMode(knobG, INPUT);
  pinMode(knobB, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  // update knob states
  knobRState = analogRead(knobR);
  knobGState = analogRead(knobG);
  knobBState = analogRead(knobB);

  // debugging/troubleshooting
  Serial.print("\n\n\n\n\n\n\n\n\n\nRed: ");
  Serial.println(knobRState);
  Serial.print("Green: ");
  Serial.println(knobGState);
  Serial.print("Blue: ");
  Serial.println(knobBState);

  // update LED components to the knob states
  analogWrite(ledR, knobRState);
  analogWrite(ledG, knobGState);
  analogWrite(ledB, knobBState);

  delay(100);
}
