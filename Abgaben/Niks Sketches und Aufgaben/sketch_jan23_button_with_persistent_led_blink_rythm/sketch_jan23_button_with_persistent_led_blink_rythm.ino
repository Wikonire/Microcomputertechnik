/* 
Mis-en-place auf Breadboard

Für Taster:
Kabel Rot von Zeile 1 +Breadboard zu 5V UNO
Wiederdatand 10K ohm column a Zeile 61 in und 60 out
1 Taster column c, Zeile 60 zu 58, 
Kabel Braun von column e, Zeile 58 auf UNO A2 

Für LED:
Kabel Blau von UNO DIGITAL 5 zu column a, Zeile 25
Wiederstand 100 ohm, column b, Zeile 25 auf Zeile 23
LED gelb +Pol column c, Zeile 23 auf Zeile 22 Minuspol
Kabel Schwarz von column d, Zeile 22 auf GND 
*/

const int buttonPin = 2;  // Taster-Pin
const int outputPin = 5;  // Output-Pin

// Variablen
unsigned long pressStartTime = 0;
unsigned long lastUpdateTime = 0;
bool isPressed = false;
bool recording = false;
unsigned long rhythm[100];  // Array zum Speichern der Intervalle
int rhythmIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT);   // Taster-Pin als Eingang
  pinMode(outputPin, OUTPUT);  // Output-Pin als Ausgang
  Serial.begin(9600);          // Debug-Ausgabe
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Taster gedrückt wird
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

  // Beenden der Aufnahme nach 10 Sekunden
  if (recording && (millis() - pressStartTime >= 10000)) {
    recording = false;
    Serial.println("Recording beendet. Wiedergabe startet.");
    playRhythm();
  }
}

void playRhythm() {
  if (!recording && rhythm[0] >=1) {
    for(int i = 0; i < sizeof(rhythm); i++) {
  Serial.println(rhythm[i]);
  }
    Serial.println('Play Rhythm');
    for (int i = 0; i < rhythmIndex; i++) {
      digitalWrite(outputPin, HIGH);
      delay(rhythm[i]);
      digitalWrite(outputPin, LOW);
      delay(200);
    }
  }
}
