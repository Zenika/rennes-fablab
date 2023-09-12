// Challenge wifi client coding
// Challenger must program an esp32 to send request to this ESP32's IP address
// Request must be a GET /ping?name=nickname
// Security check if request has not been sent from a browser (checking if user agent is present)
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define SSID "Zenika"
#define PWD ""
#define LED_MATRIX_PIN 2
#define MATRIX_H 8
#define MATRIX_W 8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
                            MATRIX_W, 
                            MATRIX_H, 
                            LED_MATRIX_PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800
                            );
WebServer server(3000);


static const uint32_t PROGMEM waitingImage[] = { 
0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c,
0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xe80f0c, 0xe80f0c, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0xe80f0c, 0xe80f0c, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0xe80f0c, 0xe80f0c, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xe80f0c, 0xe80f0c, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c,
0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c, 0xe80f0c };

static const uint32_t PROGMEM victoryImage[] = {
  0x000000, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800,
  0x000000, 0xffb800, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0xffb800,
  0x000000, 0xffb800, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0xffb800,
  0x000000, 0xffb800, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0xffb800,
  0x000000, 0x000000, 0xffb800, 0x000000, 0x000000, 0x000000, 0xffb800, 0x000000,
  0x000000, 0x000000, 0x000000, 0xffb800, 0x000000, 0xffb800, 0x000000, 0x000000,
  0x000000, 0x000000, 0x000000, 0x000000, 0xffb800, 0x000000, 0x000000, 0x000000,
  0x000000, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800, 0xffb800
};

int pixelPerChar = 6; // Width of Standard Font Characters is 8X6 Pixels
int x = matrix.width(); // Width of the Display

void setup() {
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
  initMatrix();
  Serial.println("Matrix initialized");
  initWebServer();
  Serial.println("Server initialized");
}

// Convert an RGB 8/8/8/8 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint32_t *bitmap, int16_t w, int16_t h) {
  uint16_t RGB_bmp_fixed[w * h];
  for (uint16_t pixel = 0; pixel < w * h; pixel++) {
    uint32_t b8g8r8 = bitmap[pixel];
    uint8_t b5 = ((b8g8r8 >>  0) & 0xFF) >> (8 - 5);
    uint8_t g6 = ((b8g8r8 >>  8) & 0xFF) >> (8 - 6);
    uint8_t r5 = ((b8g8r8 >> 16) & 0xFF) >> (8 - 5);
    RGB_bmp_fixed[pixel] = (r5 << 11) | (g6 << 5) | b5;
  }
  matrix.drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
  matrix.show();
}


void initMatrix() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(matrix.Color(255, 255, 255));

  fixdrawRGBBitmap(0, 0, waitingImage, 8, 8);
}

void handlePingRequest() {
  if (server.header("User-Agent").length() == 0) {
    Serial.println("Request accepted");
    server.send(200, "text/html", "OK");
    String name = server.arg("name");
    fixdrawRGBBitmap(0, 0, victoryImage, 8, 8);
    delay(4000);
    writeText(name + " Win!!");
    delay(500);
  } else {
    server.send(400, "text/html", "Cheater");
    Serial.print("Request refused - ");
    Serial.println(server.header("User-Agent"));
  }
}

void handleNotFound() {
  server.send(404, "text/html", "NOT FOUND");
}

void initWebServer() {
  server.on("/ping", handlePingRequest);
  server.onNotFound(handleNotFound); 
  const char * headerkeys[] = {"User-Agent"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
}

void loop() {
  server.handleClient();
}

void writeText(String msg) {
  int msgSize = (msg.length() * pixelPerChar) + (2 * pixelPerChar); // CACULATE message length;
  int scrollingMax = (msgSize) + matrix.width(); // ADJUST Displacement for message length;

  x = matrix.width();

  while (--x >= -scrollingMax) {

    matrix.fillScreen(0); // BLANK the Entire Screen;
    matrix.setCursor(x, 0);
    matrix.print(msg);

    matrix.show();
    delay(100);
  }
}
