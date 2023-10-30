/**
 * ESP32 anemometer sensor
 * plug sensor tu 3/3V, GND and GPIO19
 * sensor is pulled up, so signal is HIGH while it do not see magnet
 *
 *
**/

long lastInterruptMillis = 0;
float trMin = 0;

void IRAM_ATTR fonction_ISR() {
  if (lastInterruptMillis > 0) {
    long delayBtwInterrupt = millis() - lastInterruptMillis;
    trMin = 1000. / float(delayBtwInterrupt);
  }
  lastInterruptMillis = millis();
}

void setup() {
  Serial.begin(115200);
  pinMode(19, INPUT_PULLUP);
  attachInterrupt(19, fonction_ISR, FALLING);
}

void loop() {
  if (trMin > 0) {
    Serial.print(trMin);
    Serial.println("tr/min");
    trMin = 0;
  }
  delay(100);
}