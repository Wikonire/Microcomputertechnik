/*
  [ Arduino ]      [ Slider ]
     +5V  ---------  VCC
     GND  ---------  GND
     A0   ---------  OTA
          
  Gibt den Wert des Sliders aus. 
 */

const int sliderPin = A0;  //  analoge Pin, an dem der Slider hängt
int sliderValue = 0;       //  zum Speichern des Slider-Werts

void setup() {
  Serial.begin(19200);  // Starte serielle Kommunikation (baudrate ist 19200 und zeig übertragungsrate an)
}

void loop() {
  sliderValue = analogRead(sliderPin);  // Lese Slider-Wert (0-1023)
  Serial.print("Slider Value: ");
  Serial.println(sliderValue);
  delay(100);  
}
