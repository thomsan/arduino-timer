
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
#include <TouchScreen.h>
#include <Fonts/FreeSans12pt7b.h>
#include <FreeDefaultFonts.h>

// Touchscreen pressure
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// timer variables
uint32_t years, days, hours, minutes, seconds, mill;
uint32_t last_millis, current_millis, dt;
bool hasChanged = false;

// touchscreen variables
int displayXDim = 320;
int displayYDim = 240;
MCUFRIEND_kbv tft;
const int XP=8,XM=A2,YP=A3,YM=9; //ID=0x9341
const int TS_LEFT=75,TS_RT=889,TS_TOP=903,TS_BOT=97;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;
int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID;
uint8_t Orientation = 1;    //0: PORTRAIT, 1: LANDSCAPE

void setup() {
  tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    
    tft.setRotation(Orientation);

    showCounter();
    delay(1000);
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
  }
  while(minutes >= 60){
    minutes -= 60;
    hours += 1;
  }
  while(hours >= 24){
    hours -= 24;
    days += 1;
    hasChanged=true;
  }
  while(days >= 365){
    days -= 365;
    years += 1;
  }
}

void showCounter(void){
  tft.fillScreen(WHITE); // reset screen
  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(10, 180); 
  tft.setTextColor(BLACK); 
  tft.setTextSize(8); 
  tft.print(days); 
}

void readInput(){
    uint16_t xpos, ypos;  //screen coordinates
    tp = ts.getPoint();   //tp.x, tp.y are ADC values

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        // most mcufriend have touch (with icons) that extends below the TFT
        // screens without icons need to reserve a space for "erase"
        // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
        //
        // Calibration is true for PORTRAIT. tp.y is always long dimension 
        // map to your current pixel orientation
        switch (Orientation) {
            case 0:
                xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
                ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
                break;
            case 1:
                xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
                ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
                break;
            case 2:
                xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
                ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
                break;
            case 3:
                xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
                ypos = map(tp.y, TS_LEFT, TS_RT, 0, tft.height());
                break;
        }

        if(xpos > (displayXDim - displayXDim/4) && ypos > (displayYDim - displayYDim/4)){
          // + button (right bottom)
          days += 1;
          hasChanged = true;
        }

        if(xpos < (displayXDim/4) && ypos > (displayYDim - displayYDim/4)){
          // - button (left bottom)
          days -= 1;
          hasChanged = true;
        }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  updateTime();
  if(hasChanged){
    showCounter();
    hasChanged=false;
  }
  readInput();
  //delay(500);
}
