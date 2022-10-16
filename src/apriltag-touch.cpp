/*
 * The latest working code.
 * 
 * Need to add a virtual sensor for what the furnace thinks it's doing.
 */

#include "touchscreen.h"
#include <event_timer.h>

EventTimer timerDisplay;

#define DISPLAY_INTERVAL 5000UL

void setup(void) 
{
  Serial.begin(115200);
  //while(!Serial) {}
  Serial.println(F("Init"));
  
  Wire.begin();

  //needs to happen early -- before zones are initialized in ::SetupPages()
  //rtc.Init();
  
  tft.begin();
  tft.setRotation(1);

  if (!ctp.begin(40)) // pass in 'sensitivity' coefficient
  {  
    Serial.println(F("Couldn't start FT6206!"));
  }
  
  tft.fillScreen(ILI9341_BLACK);
  tft.print(F("Init"));

  activePage = SetupPages();

  timerDisplay.start(2000);
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

