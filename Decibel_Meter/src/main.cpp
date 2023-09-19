#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIGH 64

int Sensor = A3;
int Battery = A2;
double var_sensor;
double var_batery;
char buffer[100];

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset=*/U8X8_PIN_NONE);

void setup()
{
    Serial.begin(9600);
    u8g2.begin();
    pinMode(Sensor, INPUT);
    pinMode(Battery, INPUT);
}

void loop()
{   
    u8g2.setBitmapMode(1);
    var_sensor = analogRead(Sensor); // from 0 to 1023
    var_batery = analogRead(Battery); // from 0 to 1023


    u8g2.clearBuffer();
    u8g2.drawFrame(12, 18, 104, 14);


    u8g2.drawBox(14, 20, /*length of decibel bar 0 - 100*/int(var_sensor/10.2), 10);
    u8g2.drawFrame(102, 2, 24, 6);

    int head_batery = int(123 - (var_batery/51.15));
    int tail_batery = int(3+(var_batery/51.15));
    u8g2.drawBox(/*head of batery bar (100 - 0)103 - 123*/head_batery, 3, /*tail of batery bar (100 - 0)23 - 3*/tail_batery, 4);
    u8g2.drawFrame(101, 4, 2, 2);


    //Print text
    u8g2.drawLine(0, 10, 128, 10);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.drawStr(1, 8, "THCS QUe Nham");
    
    sprintf(buffer, "%d DB", int(var_sensor/7.85));
    u8g2.setFont(u8g2_font_profont22_tr);
    u8g2.drawStr(47, 49, buffer);

    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.drawStr(12, 48, "Decibel:");

    u8g2.sendBuffer();
}