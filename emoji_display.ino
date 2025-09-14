#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 18   // Push button pin

int emojiIndex = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    emojiIndex = (emojiIndex + 1) % 4;  // now cycles through 4 emojis
    showEmoji(emojiIndex);
    delay(300); // debounce
  }
}


void showEmoji(int index) {
  display.clearDisplay();

 if (index == 0) {
  // 😀 Happy Face
  display.drawCircle(64, 32, 25, SSD1306_WHITE); // face outline
  display.fillCircle(54, 25, 3, SSD1306_WHITE);  // left eye
  display.fillCircle(74, 25, 3, SSD1306_WHITE);  // right eye
  display_drawArc(64, 35, 10, 10, 20, 160, SSD1306_WHITE); // smile (approx)
} 
else if (index == 1) {
  // ☹️ Sad Face
  display.drawCircle(64, 32, 25, SSD1306_WHITE); // face outline
  display.fillCircle(54, 25, 3, SSD1306_WHITE);  // left eye
  display.fillCircle(74, 25, 3, SSD1306_WHITE);  // right eye
  display_drawArc(64, 45, 10, 10, 200, 340, SSD1306_WHITE); // sad mouth (approx)
}
else if (index == 2) {
    // 😠 Angry Face
    display.drawCircle(64, 32, 25, SSD1306_WHITE); // face outline
    display.fillCircle(54, 25, 3, SSD1306_WHITE);  // left eye
    display.fillCircle(74, 25, 3, SSD1306_WHITE);  // right eye
    // Angry eyebrows (lines)
    display.drawLine(48, 20, 56, 24, SSD1306_WHITE); // left eyebrow
    display.drawLine(72, 24, 80, 20, SSD1306_WHITE); // right eyebrow
    // Angry mouth (flat or downward curve)
    display_drawArc(64, 42, 10, 5, 200, 340, SSD1306_WHITE);
  }
  else if (index == 3) {
    // 😮 Surprised Face
    display.drawCircle(64, 32, 25, SSD1306_WHITE); // face outline
    display.fillCircle(54, 25, 3, SSD1306_WHITE);  // left eye
    display.fillCircle(74, 25, 3, SSD1306_WHITE);  // right eye
    display.drawCircle(64, 40, 6, SSD1306_WHITE);  // open mouth (circle)
  }
  display.display();
}

// Helper function: Draw Arc (approximate using lines)
void display_drawArc(int16_t x, int16_t y, int16_t w, int16_t h, int16_t startAngle, int16_t endAngle, uint16_t color) {
  for (int i = startAngle; i <= endAngle; i++) {
    float rad = i * 3.14 / 180.0;
    int x1 = x + cos(rad) * w;
    int y1 = y + sin(rad) * h;
    display.drawPixel(x1, y1, color);
  }
}
