// set active pins
int ledPin1 = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledPin4 = 11;

void setup() {
  // set pin modes
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  // lights up the LEDS in sequence
  digitalWrite(ledPin1, HIGH);
  delay(1000);
  digitalWrite(ledPin2, HIGH);
  delay(1000);
  digitalWrite(ledPin3, HIGH);
  delay(1000);
  digitalWrite(ledPin4, HIGH);
  delay(1000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
}
