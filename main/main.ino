
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
#include <Fonts/FreeSans12pt7b.h>
#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

MCUFRIEND_kbv tft;
uint32_t years, days, hours, minutes, seconds, mill;
uint32_t last_millis, current_millis, dt;
bool hasChanged = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  uint16_t ID = tft.readID();
  delay(10);
  if (ID == 0xD3) ID = 0x9481;
  delay(10);
  tft.begin(ID);
  delay(10);
  tft.setRotation(1);
  delay(10);
  tft.fillScreen(BLACK);
}

void updateTime(){
  current_millis = millis();
  dt=current_millis - last_millis;
  mill += dt;
  last_millis=current_millis;
  // TODO handle 0 overflow
  while(mill >= 1000){
    mill -= 1000;
    seconds += 1;
  }
  while(seconds >= 60){
    seconds -= 60;
    minutes += 1;
    hasChanged=true;
  }
  while(minutes >= 60){
    minutes -= 60;
    hours += 1;
  }
  while(hours >= 24){
    hours -= 24;
    days += 1;
  }
  while(days >= 365){
    days -= 365;
    years += 1;
  }
}

void printCounter(){
  tft.fillScreen(WHITE); // Bildschirm zurücksetzen
  int16_t x1, y1;
  tft.setFont(&FreeSans12pt7b); 
  tft.setCursor(10, 180); 
  tft.setTextColor(BLACK); 
  tft.setTextSize(8); 
  tft.print(seconds); 
}

void loop() {
  // put your main code here, to run repeatedly:
  updateTime();
  if(hasChanged){
    printCounter();
    hasChanged=false;
  }
  delay(500);
}
