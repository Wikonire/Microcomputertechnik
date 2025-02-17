 
 /*
 (Arduino UNO)
        +---------------------------+[Kabel Braun]
        |                           |
        +---------+[Kabel blau]    [D2]
        |         |                 | 
        |    100Ω[R] ---|           |[Taster]
        |              _|_          |
        |    [LED Gelb]\ /          |
        |               |           |
        |              [D5]         |
        |[Kabel schwarz]|           |[Kabel rot] 
        +-[GND]---------+-----------+
          [Kabel schwarz]
             
  
 */
 
 const int ledPin = 5;
 const int buttonPin = 2;
 int ledValue = 0;
 int step = 5;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  int sensorVal = digitalRead(buttonPin);
  Serial.println(sensorVal);
  if (sensorVal == HIGH) {

    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);

  }
}