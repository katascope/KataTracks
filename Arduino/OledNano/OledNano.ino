//Any byte value + CRLF on serial will add and scroll data
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

class ByteHistory
{
private:
  uint8_t history[SCREEN_HEIGHT];
public: 
  ByteHistory()
  {
    for (int i=0;i<SCREEN_HEIGHT;i++)
      history[i] = random()%255;
  }
  void Scroll(uint8_t newData)
  {
    for (int i=0;i<SCREEN_HEIGHT-1;i++)
      history[i] = history[i+1];
    history[SCREEN_HEIGHT-1] = newData;
  }  
  void Draw()
  {
    for (int y=0;y<SCREEN_HEIGHT;y++)
    {
      uint8_t len = history[y]/2;//divide by 2 to fit in 128
      display.drawLine(0, y, len, y, SSD1306_WHITE);
    }
  }
};
ByteHistory byteHistory;

void loop() {
  if (Serial.available())
  {
    String t = "";
    while (Serial.available())
    {
      char ch = (char)Serial.read();      
      if (ch != 10 && ch != 13)
        t += ch;  
    }
    char buf[t.length()+1];
    t.toCharArray(buf, t.length()+1);    
    uint8_t v = (uint8_t)atoi(buf);
    byteHistory.Scroll(v);
  }
  byteHistory.Draw();
  display.display();  
}
