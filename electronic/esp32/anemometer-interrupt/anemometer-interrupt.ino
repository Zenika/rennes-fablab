/**
 * ESP32 anemometer sensor
 * plug sensor tu 3/3V, GND and GPIO19
 * sensor is pulled up, so signal is HIGH while it do not see magnet
 *
 *
**/
#include <WiFi.h>
#include <HTTPClient.h>
String serverUrl = "http://192.168.111.179:3000/sensor";
#define SSID "SSID"
#define PWD "PWD"

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
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
  attachInterrupt(19, fonction_ISR, FALLING);
  
}

void loop() {
  if (trMin > 0 && WiFi.status() == WL_CONNECTED) {
  Serial.print(trMin);
  Serial.println("tr/min");
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"wind\": " + String(trMin) + "}");
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    trMin = 0;
  }
  delay(100);
}