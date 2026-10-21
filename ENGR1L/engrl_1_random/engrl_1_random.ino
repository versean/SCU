int piezoPin = 3;
int wait = 500;
int freq = 200;

void setup() {
  pinMode(piezoPin, OUTPUT);
  // put your setup code here, to run once:
  for (int i = 5; i > 0; i--) {
    for (int j = 0; j < 3; j++) {
      tone(piezoPin, freq, wait/2);
      delay(wait);
      freq += 20;
    }
    wait = wait / 1.25;
  }
  
}

void loop() {

}
