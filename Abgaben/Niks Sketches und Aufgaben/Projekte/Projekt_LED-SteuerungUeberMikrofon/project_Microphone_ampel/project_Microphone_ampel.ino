const int soundSensor = 13;  // Digitaler Eingang
const int analogPin = A0;    // Analoger Eingang (optional)
const int ledPinGreen = 11;  // Grüne LED
const int ledPinYellow = 6;  // Gelbe LED
const int ledPinRed = 5;     // Rote LED

void setup() {
    pinMode(soundSensor, INPUT);
    pinMode(ledPinGreen, OUTPUT);
    pinMode(ledPinYellow, OUTPUT);
    pinMode(ledPinRed, OUTPUT);
    Serial.begin(19200);  // Baudrate für MIDI-Kommunikation, falls relevant
}

void loop() {
    int soundState = digitalRead(soundSensor);
    int soundLevel = analogRead(analogPin);
    int brightness = map(soundLevel, 0, 1023, 0, 255);

    Serial.print("Sound Level: ");
    Serial.print(soundLevel);
    Serial.print(" -> LED Helligkeit: ");
    Serial.println(soundLevel);

    // LEDs je nach Lautstärke steuern
    if (soundLevel > 5) {
        digitalWrite(ledPinGreen, brightness/2); // Leise Geräusche -> grüne LED dimmen
        digitalWrite(ledPinYellow, 0);
        digitalWrite(ledPinRed, 0);
    } 
     if (soundLevel > 10) {
        digitalWrite(ledPinYellow, soundLevel); // Mittlere Geräusche -> gelbe LED dimmen
        digitalWrite(ledPinGreen, soundLevel);
        digitalWrite(ledPinRed, 0);
    } 
    if (soundLevel > 15){
        digitalWrite(ledPinRed, soundLevel); // Laute Geräusche -> rote LED dimmen
        digitalWrite(ledPinGreen, soundLevel);
        digitalWrite(ledPinYellow, soundLevel);
    }

    delay(50);
}