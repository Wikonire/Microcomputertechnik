/* blinking LED with random delays for LED at D5 and LED at D6*/
const int ledPinOne = 5; 
const int ledPinTwo = 6; 

void setup() {
  pinMode(ledPinOne, OUTPUT);
  pinMode(ledPinTwo, OUTPUT);

}

void loop() {
loopBlink(600, 200, ledPinOne);
loopBlink(900, 300, ledPinTwo);
}

void loopBlink(long maxDelayOn, long maxDelayOff, int ledPin ) {
  digitalWrite(ledPin, HIGH);
  delayRandomNumber(maxDelayOn);
  digitalWrite(ledPin, LOW);
  delayRandomNumber(maxDelayOff);
}

void delayRandomNumber(long max) {
  const long time = random(1, max);
  delay(time);
}

