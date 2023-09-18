#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIGH 64

int Sensor = A3;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset=*/U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset=*/U8X8_PIN_NONE);
static const unsigned char image_Volup_8x6_bits[] U8X8_PROGMEM = {0x48,0x8c,0xaf,0xaf,0x8c,0x48};

int progress = 0; // progress of the progressbar
char buffer[32]; // helper buffer to construct a string to be displayed

void setup()
{
  Serial.begin(9600);
  u8g2.begin();

  pinMode(Sensor, INPUT);
}

void loop()
{
  int var = analogRead(Sensor);
  Serial.println(var);

  u8g2.clearBuffer();

  u8g2.setBitmapMode(1);
  u8g2.drawLine(0, 10, 127, 10);
  u8g2.drawFrame(105, 2, 21, 7);
  u8g2.drawFrame(103, 4, 2, 3);
  u8g2.drawFrame(13, 25, 103, 14);
  // DB do duoc
  if(var > 30) {
    u8g2.drawBox(15, 27, var/10 - 3, 10);
  }
  else {
    u8g2.drawBox(15, 27, 0, 10);
  }
  // Print Decibel
  u8g2.setFont(u8g2_font_helvB08_tr);
  u8g2.drawStr(25, 50, "Decibel: ");
  // Print number
  sprintf(buffer, "%d DB", var/10);
  u8g2.setFont(u8g2_font_helvB08_tr);
  u8g2.drawStr(71, 50, buffer);

  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(1, 9, "THCS Que Nham");
  u8g2.drawXBMP( 92, 3, 8, 6, image_Volup_8x6_bits);
  // Dung luong Pin con lai
  u8g2.drawBox(120, 2, 19, 7);

  u8g2.sendBuffer();

  
  delay(100);
}