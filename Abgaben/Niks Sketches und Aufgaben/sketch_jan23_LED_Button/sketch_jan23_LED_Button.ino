


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

class State {
  private:
   bool isOn = false;
   int duration = 200;
   public:
    State(bool isOn) {
      this->isOn = isOn;
      this->duration = duration;
    }

    State getState() {
      return this;
    }
  };

const int buttonPin = 2;
const int ledPin = 5;
const int resetTime = 3000;
int buttonState = 0;
int resetTimer = 0;
State *stateList[100];



void setup() {
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println("loop");
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    if(resetTimer> resetTime) {
      resetTimer = 0;
      stateList = State[100];
    } else {
      resetTimer++;
      
    }


    digitalWrite(ledPin, HIGH);
    Serial.println("on");
    delay(300);
  } 
  digitalWrite(ledPin, LOW);
  
}
