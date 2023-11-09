/*
 * Use LM35(D) chip, plug vcc to 3.3v / 5v, GND to GND and out to GPIO34
 * We use specific function analogReadMilliVolts because LM35 is a linear temperature sensor
 * based on 1°c/10mV
 */

#define PIN_LM35       34 // ESP32 pin GPIO34 (ADC6) connected to LM35

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read the millivolt value from the temperature sensor
  float milliVolt = analogReadMilliVolts(PIN_LM35);

  float tempC = milliVolt / 10;
  // convert the °C to °F
  float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");

  delay(300);
}