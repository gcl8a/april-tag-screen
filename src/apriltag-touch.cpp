/*
 * The latest working code.
 * 
 * Need to add a virtual sensor for what the furnace thinks it's doing.
 */

#include "touchscreen.h"
#include <event_timer.h>

EventTimer timerDisplay;

#include <Adafruit_GFX.h>      // Core graphics library
//#include <Adafruit_ILI9341.h>  //display
//#include <Adafruit_FT6206.h>   //touchscreen
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 tft(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define DISPLAY_INTERVAL 5000UL

void setup(void) 
{
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println(F("Init"));
  
  Wire.begin();

  //needs to happen early -- before zones are initialized in ::SetupPages()
  //rtc.Init();
  
  tft.begin();
  //tft.setRotation(1);

  // if (!ctp.begin(40)) // pass in 'sensitivity' coefficient
  // {  
  //   Serial.println(F("Couldn't start FT6206!"));
  // }
  tft.drawPixel(10, 10, SSD1306_WHITE);

  //tft.fillScreen(SSD1306_WHITE);
  //tft.print(F("Init"));

  activePage = SetupPages();

  timerDisplay.start(2000);

  while(1) {}
}

void loop() 
{
  if(timerDisplay.CheckExpired()) redraw = true; //refresh the screen

  // if(ctp.touched()) 
  // {
  //   // Retrieve the point  
  //   TS_Point p = ctp.getPoint();
    
  //   // transform the point to the rotated system
  //   int x = 320 - p.y; 
  //   int y = p.x;       
    
  //   if(activePage->HandleClick(x, y))
  //     redraw = true; //could be made more efficient
  // }

  if(redraw) 
  {
    if(activePage) 
    {
      activePage->Draw();
    }

    timerDisplay.Start(2000);

    redraw = false;
  }
}

