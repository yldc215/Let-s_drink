
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

int buttonPin_1 = 2;                // 按键的管脚定义
int buttonPin_2 = 4;                // 按键的管脚定义
int buttonPin_3 = 8;                // 按键的管脚定义
int buttonPin_4 = 9;                // 按键的管脚定义

int buttonState_1 = 0;              // 存储按键状态值
int buttonState_2 = 0;              // 存储按键状态值
int buttonState_3 = 0;              // 存储按键状态值
int buttonState_4 = 0;              // 存储按键状态值

void setup() {
  u8g2.begin();
  pinMode(buttonPin_1, INPUT_PULLUP);            //设置按键管脚上拉输入模式
  pinMode(buttonPin_2, INPUT_PULLUP);            //设置按键管脚上拉输入模式
  pinMode(buttonPin_3, INPUT_PULLUP);            //设置按键管脚上拉输入模式
  pinMode(buttonPin_4, INPUT_PULLUP);            //设置按键管脚上拉输入模式

  analogReference(INTERNAL);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  u8g2.begin();
  dht.begin();
}

uint8_t m = 30;

char h_str[3];
char t_str[3];
float h;
float t;

void loop() {

  buttonState_1 = digitalRead(buttonPin_1);       //读取按键返回状态值
  buttonState_2 = digitalRead(buttonPin_2);       //读取按键返回状态值
  buttonState_3 = digitalRead(buttonPin_3);       //读取按键返回状态值
  buttonState_4 = digitalRead(buttonPin_4);       //读取按键返回状态值

  char m_str[3];
  strcpy(m_str, u8x8_u8toa(m, 2));    

  t = dht.readTemperature();//读温度(摄氏度)
  strcpy(t_str, u8x8_u8toa(t, 2));
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fur20_tf);
    u8g2.drawStr(0, 23, "T");
    u8g2.drawStr(20, 23, ":");
    u8g2.drawStr(40, 23, m_str);
    u8g2.drawStr(80, 23, "C");
    u8g2.drawStr(0, 40, "---------------");

    u8g2.drawStr(0, 63, "T");
    u8g2.drawStr(20, 63, ":");
    u8g2.drawStr(40, 63, t_str);
    u8g2.drawStr(80, 63, "C");
  } while ( u8g2.nextPage() );
  delay(100);

  if (buttonState_1 == LOW) {                 // 若按键被按下
    delay(10);                                //等待跳过按键抖动的不稳定过程
    if (buttonState_1 == LOW)                 // 若按键被按下
    {
      m++;                                     //设定的温度增加1
    }
  }
   if (buttonState_2 == LOW) {                 // 若按键被按下
    delay(10);                                 //等待跳过按键抖动的不稳定过程
    if (buttonState_2 == LOW)                  // 若按键被按下
    {
      m--;                                     //设定的温度减小1
    }
  }

  if (t >= m )
  {
    analogWrite(11, 200);
  }
   if (buttonState_3 == LOW) {                // 若按键被按下
    delay(10);                                //等待跳过按键抖动的不稳定过程
   if (buttonState_3 == LOW)                  // 若按键被按下
    {
      digitalWrite(11, LOW);                  //蜂鸣器停止响
    }
  }

}


