/* blinking LED with random delays between 1 until 200 milliseconds*/
const int ledPin = 5; 

void setup() {
  pinMode(ledPin, OUTPUT);

}

void loop() {
  digitalWrite(ledPin, HIGH);
  delayRandomNumber();
  digitalWrite(ledPin, LOW);
  delayRandomNumber();

}

void delayRandomNumber() {
  const long time = random(1, 200);
  delay(time);
}

