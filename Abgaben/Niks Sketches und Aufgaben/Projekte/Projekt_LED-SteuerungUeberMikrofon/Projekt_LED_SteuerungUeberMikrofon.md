# Musikvisualisierung mit WPSE309 Mikrofon und einzelnen LEDs

## Projektziel
Ich möchte LEDs mit einem WPSE309 Mikrofon-Sound-Sensor und einem Arduino Uno R3 steuern. Die LEDs sollen je nach Lautstärke unterschiedlich aufleuchten.

## Benötigte Hardware
- Arduino Uno R3
- WPSE309 Mikrofon-Sound-Sensor
- 5 LEDs (Grün, Gelb, Blau, Rot, Weiß)
- 5 Widerstände (220Ω - 1kΩ für jede LED)
- Jumper-Kabel
- Breadboard

## Schaltung
### WPSE309 Mikrofon → Arduino
| WPSE309 Pin | Arduino Pin | Beschreibung |
|------------|------------|--------------|
| VCC        | 5V         | Stromversorgung |
| GND        | GND        | Masse |
| A0         | A0         | Analoge Ausgabe (Lautstärkewert) |

### LEDs → Arduino
| LED Farbe | Arduino Pin | Vorwiderstand |
|----------|------------|--------------|
| Grün     | 3          | 220Ω - 1kΩ |
| Gelb     | 5          | 220Ω - 1kΩ |
| Blau     | 6          | 220Ω - 1kΩ |
| Rot      | 9          | 220Ω - 1kΩ |
| Weiß     | 10         | 220Ω - 1kΩ |

Die LEDs werden über Widerstände an den digitalen Pins des Arduino angeschlossen.

## Code für die LED-Steuerung
```cpp
const int micPin = A0; // Mikrofon an A0

// LED Pins
const int ledGreen = 3;
const int ledYellow = 5;
const int ledBlue = 6;
const int ledRed = 9;
const int ledWhite = 10;

void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soundLevel = analogRead(micPin);  // Mikrofonwert auslesen
  Serial.println(soundLevel);  // Debugging: Zeigt den Wert im Serial Monitor

  // LEDs basierend auf Lautstärke aktivieren
  if (soundLevel > 500) {
    digitalWrite(ledGreen, HIGH);
  } else {
    digitalWrite(ledGreen, LOW);
  }

  if (soundLevel > 600) {
    digitalWrite(ledYellow, HIGH);
  } else {
    digitalWrite(ledYellow, LOW);
  }

  if (soundLevel > 700) {
    digitalWrite(ledBlue, HIGH);
  } else {
    digitalWrite(ledBlue, LOW);
  }

  if (soundLevel > 800) {
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(ledRed, LOW);
  }

  if (soundLevel > 900) {
    digitalWrite(ledWhite, HIGH);
  } else {
    digitalWrite(ledWhite, LOW);
  }

  delay(10); // Kleiner Delay für bessere Reaktion
}
```

## Funktionsweise
Das WPSE309 Mikrofon misst den Schallpegel und gibt diesen als analogen Wert (`A0`) aus.  
Der Arduino liest diesen Wert aus (`analogRead(A0)`) und zeigt ihn im Serial Monitor an.

Je nach Lautstärke schalten sich verschiedene LEDs ein oder aus:

- **Grün** → leuchtet ab **500**
- **Gelb** → leuchtet ab **600**
- **Blau** → leuchtet ab **700**
- **Rot** → leuchtet ab **800**
- **Weiß** → leuchtet ab **900** (sehr laut)

Die Schwellenwerte können angepasst werden, falls das Mikrofon andere Werte liefert.

## Erweiterungen
- **Feinjustierung**: Anpassung der Schwellenwerte, um die Reaktion an den Raum anzupassen.
- **Mehr Dynamik**: Statt LEDs nur an/aus zu schalten, kann ich sie mit `analogWrite()` dimmen.
- **Farben kombinieren**: Mehrere LEDs gleichzeitig leuchten lassen, um Mischfarben zu erzeugen.  
