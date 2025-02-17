/*
  Mis-en-place: 
  Breadboard Rot 1 (+) -> UNO 5V
  Breadboard Schwarz 1 - -> UNO GND

  Breadboard Rot (+) 5 -> a6
  Breadboard Taster d6 -> d7
  Breadboard Kabel Blau e7 -> DIGITAL 2
  Breadboard Wiederstand 10k ohm b7 -> b15
  Breadboard Kabel Schwarz a15 -> (-)15


  Breadboard  Kabel Orange j30 -> DIGITAL 5
  Breadboard Wiederstand h30 -> h35
   Breadboard  LED Gelb i35 -> i36
  Breadboard Kabel Braun j36 -> GND
*/

// Pins
const int buttonPin = 2;  // Taster-Pin
const int outputPin = 5;  // Output-Pin

// Variablen
unsigned long pressStartTime = 0;
unsigned long lastUpdateTime = 0;
bool isPressed = false;
bool recording = false;
unsigned long rhythm[100]; // Array zum Speichern der Intervalle
int rhythmIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);       
  Serial.begin(9600);               
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !isPressed) {
    isPressed = true;
    pressStartTime = millis();
    if (!recording) {
      recording = true;
      rhythmIndex = 0;
      Serial.println("Recording gestartet.");
    }
  }

  // Wenn Taster losgelassen wird
  if (buttonState == HIGH && isPressed) {
    isPressed = false;
    unsigned long pressDuration = millis() - pressStartTime;

    // Speichere die Dauer im Rhythmus-Array
    if (recording && rhythmIndex < 100) {
      rhythm[rhythmIndex++] = pressDuration;
      Serial.print("Press duration recorded: ");
      Serial.println(pressDuration);
    }
  }

  if (recording && (millis() - pressStartTime >= 10000)) {
    recording = false;
    Serial.println("Recording beendet. Wiedergabe startet.");
    playRhythm();
  }
}

void playRhythm() {
  for (int i = 0; i < rhythmIndex; i++) {
    digitalWrite(outputPin, HIGH);
    delay(rhythm[i]);
     Serial.println(rhythm[i]);
    digitalWrite(outputPin, LOW);
    delay(100);
  }
}

