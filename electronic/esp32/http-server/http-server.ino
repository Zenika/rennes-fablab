// Experiment wifi server of ESP32

#include <WiFi.h>
#include <WebServer.h>

#define SSID "zenika"
#define PWD "zenika"

WebServer server(3000);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
  initWebServer();
  Serial.print("Server initialized");
}

void handlePingRequest() {
  server.send(200, "text/html", "OK");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void handleNotFound() {
  server.send(404, "text/html", "NOT FOUND");
}

void initWebServer() {
  server.on("/ping", handlePingRequest);
  server.onNotFound(handleNotFound); 
  server.begin();
}

void loop() {
  server.handleClient();
}
