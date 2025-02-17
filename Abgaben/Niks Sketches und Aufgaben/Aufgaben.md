# Dokumentation und Lösung der Aufgaben im Fach Mikrocomputertechnik, TEKO
## Aufgaben Übersicht mit Verweis auf Sketches:
**Übung 4.1 (Timing)**
-  [Übung 4.1 (Timing)](#übung-41-timing)
- `-`

**Übung 4.2 (Dynamischer Blinker)**
- [Übung 4.2 (Dynamischer Blinker)](#übung-42-dynamischer-blinker)
- `sketch_jan23_dynamic_blink`

**Übung 4.3 (Pull-Up-Widerstand)**
- [Übung 4.3 (Schaltung mit Pull-Up Widerstand)](#übung-43-schaltung-mit-pull-up-widerstand)
- `sketch_jan30_Pull-up`

**Übung 4.4 (Taster mit Pull-Up)**
- [Übung 4.4 (Taster mit Pull-Up)](#übung-44-pull-up-und-pull-down-widerstände)
- `sketch_jan23_LED_Button`
- `sketch_jan23_Print_button_State`

**Übung 4.5 (Dimmer mit Taster)**
- [Übung 4.5 (Dimmer mit Taster)](#übung-45-interrupt)
- `sketch_janDimUp-Down`

**Übung 4.6 (Fade-In, Fade-Out)**
- [Siehe auch Übung 4.6 (Dimmer mit Taster)](#aufgabedimmer-mit-taster)
- `-`

**Übung 4.7 (Interrupt-gesteuertes Ein-/Ausschalten)**
- `sketch_jan30_interrupt-led`

**Übung 4.8 (Interrupt mit Entprellung und Fade-Effekt)**
- `-`



## Übung 4.1 (Timing)
### Wie ist die Zahl in der Funktion delay() zu verstehen? 
```
void delay(unsigned long ms)
```
Die Zahl in der Funktion `delay()` gibt die Dauer der Unterbrechung des Programms in Millisekunden an. Während dieser Zeit pausiert das Arduino-Board die Ausführung aller weiteren Befehle.

**Beispiel:**
```
delay(1000); // Pausiert das Programm für eine Sekunde
```
**Quelle:** [Arduino Language Reference](https://docs.arduino.cc/language-reference/en/functions/time/delay/)

### Weitere Funktionen zum Timing

#### `void delayMicroseconds(unsigned int us)`
- Hält das Programm für die angegebene Zeit in Mikrosekunden an.
- Maximale Genauigkeit bis 16383 Mikrosekunden.

#### `unsigned long millis()`
- Gibt die Anzahl der Millisekunden seit dem Start des Programms zurück.
- Nach ca. 50 Tagen erfolgt ein Überlauf auf 0.

#### `unsigned long micros()`
- Gibt die Anzahl der Mikrosekunden seit dem Start des Programms zurück.
- Nach ca. 70 Minuten erfolgt ein Überlauf auf 0.

### Geschwindigkeit des Arduino messen
Ein einfaches Vorgehen zur Bestimmung der Durchlaufzeit der `loop()`-Funktion ist:
```
unsigned long startTime = millis();
loop();
unsigned long duration = millis() - startTime;
Serial.println(duration);
```
Dadurch erhält man die Dauer eines Durchlaufs in Millisekunden.

## Übung 4.2 (Dynamischer Blinker)
### Aufgabe:
Erstelle ein Blinkmuster, bei dem sich das Verhältnis von Ein- zu Ausschaltzeit dynamisch verändert:
```
const int ledPin = 5;
int onTime = 500;
int offTime = 1500;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(onTime);
  digitalWrite(ledPin, LOW);
  delay(offTime);

  onTime += 50;
  offTime -= 50;
  if (onTime > 1500 || offTime < 500) {
    onTime = 500;
    offTime = 1500;
  }
}
```

## Übung 4.3 (Schaltung mit Pull-Up Widerstand)
Baue die aktuelle Schaltung so um, dass ein Pull-Up Widerstand genutzt wird, und passe den Code entsprechend an:

### Schaltung:
```
Vcc (5V)
  |
  |
 [R]  (10kΩ)
  |
  |------> Eingangspin
  |
  | (Taster)
  |
 GND
```

### Code:
```c
const int ledPin = 5;
const int buttonPin = 2;
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50); // Entprellung
    if (digitalRead(buttonPin) == LOW) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      while (digitalRead(buttonPin) == LOW);
    }
  }
}
```

## Übung 4.4 (Pull-Up und Pull-Down Widerstände)
### Interne Pull-Ups und Pull-Downs
- **Digitale Pins (D0–D13)** haben interne Pull-Up-Widerstände.
- **Analoge Pins (A0–A5, wenn als digital genutzt)** haben ebenfalls interne Pull-Ups.
- **Arduino hat keine internen Pull-Down-Widerstände!** Falls benötigt, muss ein externer Widerstand (z. B. 10kΩ) verwendet werden.

### Pull-Up-Schaltung
```c
pinMode(pin, INPUT_PULLUP);
```
Schaltung:
```
Vcc (5V)
  |
  |
 [R]  (10kΩ)
  |
  |------> Eingangspin
  |
  | (Taster)
  |
 GND
```

### Pull-Down-Schaltung
Falls Pull-Down gewünscht, muss ein externer Widerstand genutzt werden:
```
Vcc (5V)
  |
  | (Taster)
  |
  |------> Eingangspin
  |
 [R]  (10kΩ)
  |
  |
 GND
```

### Code:
```c
pinMode(buttonPin, INPUT);
```

## Übung 4.5 Interrupt

### Interrupt Aufgabe: 

```
(Arduino UNO)
[D2]+---------------------------+[Kabel Braun]
  |       [Kabel blau]          |
  [D5]+---------+             [D2]
  |               |[D5]        |
  |    100Ω[R] ---+            |[Taster]
  |              _|_           |
  |    [LED Gelb]\ /           |
  |               |            |
  |               |            |
  |[Kabel schwarz]|            |[Kabel rot]
  +-[GND]---------+-----------+
[Kabel schwarz]
```




Drücken von Taster löscht LED langsam, loslassen lässt LED langsam erhellen.
```
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
```



### Aufgabe:(Dimmer mit Taster)
Drücken des Tasters dimmt die LED langsam herunter, Loslassen der Taste lässt die LED langsam heller werden.

### Schaltung:
```
 (Arduino UNO)
    [D2]+---------------------------+[Kabel Braun]
        |                           |
    [D5]+---------+[Kabel blau]    [D2]
        |               |[D5]       | 
        |    100Ω[R] ---+          [Taster]
        |              _|_          |
        |    [LED Gelb]\ /          |
        |               |           |
        |               |           |
        |[Kabel schwarz]|           |[Kabel rot] 
        +-[GND]---------+-----------+
          [Kabel schwarz]
             
```


### Code:
```
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
```
