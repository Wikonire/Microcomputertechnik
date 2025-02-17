
/*
 (Arduino UNO)
    [D2]+---------------------------+[Kabel Braun]
        |                           |
    [D5]+---------+[Kabel blau]    [D2]
        |         |[D5]             | 
        |    100Ω[R] ---+           |[Taster]
        |              _|_          |
        |    [LED Gelb]\ /          |
        |               |           |
        |               |           |
        |[Kabel schwarz]|           |[Kabel rot] 
        +-[GND]---------+-----------+
          [Kabel schwarz]
             
  
  Drücken von Taster löscht LED langsam, loslassen lässt LED langsam erhellen. 
 */

const int ledPin = 5;
const int buttonPin = 2;
int ledValue = 0;

void InterruptHandler() {
  if (ledValue<=0) {
    for ( ledValue; ledValue <= 255; ledValue++) {
      Serial.println("UP");
      analogWrite(ledPin, ledValue);
    }

  } else {
    for (ledValue; ledValue >= 0; ledValue--) {
      Serial.println("->Down");
      analogWrite(ledPin, ledValue);
    }
  }
  Serial.println("Done");
}




void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  analogWrite(ledPin, ledValue);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), InterruptHandler, FALLING);
}



void loop() {
}
