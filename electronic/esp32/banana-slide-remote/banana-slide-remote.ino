/*
 * Install keyboard lib from https://github.com/T-vK/ESP32-BLE-Keyboard
 *
 *
 *
 *
 **/


/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
 
//#define USE_NIMBLE
#define TOUCH_IO 15
int capacitiveValue = 100; // global variable avoid reallocation
int threshold = 20; // to be adjusted

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    capacitiveValue = touchRead(TOUCH_IO);
    if(capacitiveValue < threshold){
      Serial.println("Press right");
      bleKeyboard.write(KEY_RIGHT_ARROW);
      delay(300);
    }
  }
}