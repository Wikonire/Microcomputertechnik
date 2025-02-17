
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
int step = 1;
int delayStep = 25;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int sensorVal = digitalRead(buttonPin);
  analogWrite(ledPin, ledValue);
  if (sensorVal == HIGH) {
    dimUp();
  } else {
    dimDown();
  }
}


void dimUp() {
  if (ledValue >= 255) {
    ledValue = 255;
    analogWrite(ledPin, ledValue);
  } else {
    ledValue = ledValue + step;
    analogWrite(ledPin, ledValue);
    Serial.println("DimUp");
    Serial.println(ledValue);
    delay(delayStep);
  }
}

void dimDown() {

  if (ledValue <= 0) {
    ledValue = 0;
    analogWrite(ledPin, ledValue);
  } else {
    ledValue = ledValue - step;
    analogWrite(ledPin, ledValue);
    Serial.println(ledValue);
    Serial.println("DimDown");
    delay(delayStep);
  }
}