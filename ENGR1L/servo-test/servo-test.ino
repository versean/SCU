#include <Servo.h>

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(10);
  myservo.write(135);
}

void loop() {
  // put your main code here, to run repeatedly:

}
