#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int trigPin = 9;  // 
const int echoPin = 10; //

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  u8g2.begin();
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance > 50) distance = 50;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "TAVOLSAG:");

    char buf[10];
    sprintf(buf, "%d cm", distance);
    u8g2.drawStr(80, 15, buf);

    if (distance < 10) {
      u8g2.drawFrame(0, 20, 128, 44);
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(30, 48, "STOP!");
    } else {
      int barLen = map(distance, 0, 50, 0, 128);
      u8g2.drawBox(0, 30, barLen, 20);
    }

  } while ( u8g2.nextPage() );

  delay(50); 
}
