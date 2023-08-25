// install Adafruit_GFX, Adafruit_NeoMatrix and Adafruit_NeoPixel
// code for WS2812 

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

int matrixW = 8;
int matrixH = 8;
#define PIN 2

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
                            matrixW, 
                            matrixH, 
                            PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800
                            );


int pixelPerChar = 6; // Width of Standard Font Characters is 8X6 Pixels
int x = matrix.width(); // Width of the Display


void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(matrix.Color(255, 255, 255));
}

void loop() {
  char exampleText[] = "Hello World Zenika!";
  writeText(exampleText);
  delay(1000);

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