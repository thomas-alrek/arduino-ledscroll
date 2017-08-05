#include <Colorduino.h>
//#include <ColorTools.h>
#include "font.h"

char message[] = "Scrolling text!";

unsigned char whiteBalVal[3] = {36,63,63};
int r = 0;
int g = 64;
int b = 0;

int offset;

void setup() {
  Serial.begin(9600);
  Colorduino.Init();
  Colorduino.SetWhiteBal(whiteBalVal);
  offset = 8;
}

void loop() {
  clear();
  for (int i = 0; i < sizeof(message); i++) {
      drawChar(message[i], (8 * i) + offset);
  }
  if (offset < (-(signed int) (sizeof(message) - 1) * 8)) {
    offset = 8;
  } else {
    offset--;
  }
  render();
  delay(128);
}

void render() {
  Colorduino.FlipPage();
}

void SetPixel(int x, int y, bool val) {
  if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
    Colorduino.SetPixel(x, y, r * val, g * val, b * val);
  }
}

void clear() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      Colorduino.SetPixel(x, y, 0, 0, 0);
    }
  }
}

void drawChar(char c, int offset) {
  c -= 32;
   offset *= -1; 
  c = c < 0 ? 0 : c > 93 ? 0 : c;
  for (int y = 0; y < 8; y++) {
    byte f = font[c][y];
    for (int x = 0; x < 8; x++) {
      if (x + offset > 7 || x + offset < -8) {
        break;
      }
      if (bitRead(f, 7 - x)) {
        SetPixel(x + offset, y + 1, true);
      }
    }
  }
}
