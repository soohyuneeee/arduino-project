
#include <DS1302.h>

#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <avr/power.h>
#ifdef __AVR__
#define CLK 12
#define DAT 11
#define RST 10
#endif
#define PIN 7
#define NUMPIXELS 8

DS1302 rtc(RST, DAT, CLK);
LiquidCrystal_I2C lcd(0X27,16,2);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup(){
  lcd.init();
  lcd.backlight();

  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(MONDAY);
  rtc.setTime(10,30,0);
  rtc.setDate(06,07,2021);
  pinMode(7, OUTPUT); //led 코드
  Serial.begin(9600);//통신
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
}
void loop(){
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(0,1);
  lcd.print(rtc.getDOWStr());
  lcd.setCursor(8,1);
  lcd.print(rtc.getTimeStr());
  int cds = analogRead(A0);//초기화
  Serial.println(cds);//출력
  if (cds > 800)//조도 센서 값이 800초과이면
  {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255 , 255));//색 지정
      pixels.show();//불키기
      
    }
  }
  else//800미만일 때 
  {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0 , 0));//색 초기화
      pixels.show();//끄기
      //0.2초
    }
  }
}
  
