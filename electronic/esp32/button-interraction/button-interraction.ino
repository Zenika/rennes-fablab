// Experiment touch capacity of ESP32
// https://drive.google.com/file/d/1dDHLeIwraGGjLoAxMODwVY9fUQPS52iL/view?resourcekey
// link a LED with adapted resistor to pin 23
// link pin 15 and 4 to a metalic surface
// then touch metalic surface with your finger to light on LEDs

#define SHAKER_LED 23
#define SHAKER_TOUCH 15
#define SPOON_TOUCH 4
int capacitiveValue = 100;
int threshold = 20;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SHAKER_LED, OUTPUT);
}

void loop() {
  capacitiveValue = touchRead(SPOON_TOUCH);
  if(capacitiveValue < threshold){
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  capacitiveValue = touchRead(SHAKER_TOUCH);
  if(capacitiveValue < threshold){
    digitalWrite(SHAKER_LED, HIGH);
  } else {
    digitalWrite(SHAKER_LED, LOW);
  }
}
