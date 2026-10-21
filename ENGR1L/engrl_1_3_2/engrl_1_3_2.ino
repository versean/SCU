/* VideoGameSound with Arduino
   Author: Dr. JAK
   Date: 10/25/15 */
   
int pin=9;

void setup() {
  pinMode(pin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int duration=15;duration>=1;duration=duration-1){
    for(int freq=1700;freq<=2300;freq=freq+20){
      tone(pin,freq,duration);
      Serial.print(freq);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}
