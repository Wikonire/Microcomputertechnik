/*
  Mis-en-place: 
  Breadboard Rot 1 (+) -> UNO 5V
  Breadboard Schwarz 1 - -> UNO GND

  Breadboard Rot (+) 5 -> a6
  Breadboard Taster d6 -> d7
  Breadboard Kabel Blau e7 -> DIGITAL 2
  Breadboard Wiederstand 10k ohm b7 -> b15
  Breadboard Kabel Schwarz a15 -> (-)15


*/

const int buttonPin = 2;
int buttonState = 0;

void setup() {
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(buttonPin, INPUT);
}

void loop() {
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println("loop");
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH, print on:
  if (buttonState == HIGH) {
    Serial.println("on");
  } 
  delay(100);
}
