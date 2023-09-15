/**
 *  SERIAL PLOTTER EXAMPLE
 *
 * Example made with an esp32 Dev Module and a joystick
 * plug 3.3v and GND to joystick
 * plug analogs output of the joystick to pin 34 & 35
 * plug "click" digital output of the joystick to pin 32
 *
 * Start sketch and open serial plotter tool
 *
 *
**/


void setup() {
  Serial.begin(115200);
  pinMode(32, INPUT_PULLUP);
}

void loop() {
  Serial.print("x:");
  Serial.print(analogRead(34));
  Serial.print(",y:");
  Serial.print(analogRead(35));
  Serial.print(",click:");
  Serial.println(digitalRead(32) * 4096);
  delay(50);
}
