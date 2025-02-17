
/*
  Mis-en-place: 
  Breadboard: Rot 1 + -> UNO 5V
  Breadboard 
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
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("on");
  } 
  delay(500);
}
