/*
 * The latest working code.
 * 
 * Need to add a virtual sensor for what the furnace thinks it's doing.
 */

#include "touchscreen.h"
#include <event_timer.h>
#include <tag-widget.h>
#include <button.h>

Screen screen;

#define DISPLAY_INTERVAL 2000UL
#define REFRESH_INTERVAL 5000UL

EventTimer timerRefresh;
EventTimer timerDisplay;

Page* pageBlank = new Page(&screen);
Page* pageTag = new Page(&screen);

Button button9(9);

void SetupPages(void)
{
    Serial.println(F("SetupPages"));

    pageTag->AddWidget(new TagWidget(&screen, 32, 96, 0, 64, 1));
    pageBlank->AddWidget(new RectangularWidget(&screen, 32, 96, 0, 64, NONE));
    
    button9.init();

    Serial.println(F("/SetupPages"));
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.println(F("Init"));
  
  Wire.begin();
  
  screen.begin();
  screen.clearDisplay();
  screen.display();

  SetupPages();

  timerRefresh.start(REFRESH_INTERVAL);
}

void loop() 
{
  if(button9.checkButtonPress())
  {
    screen.SetActivePage(pageTag);
    screen.CheckRedraw();
    timerDisplay.Start(DISPLAY_INTERVAL);
  }

  if(timerDisplay.CheckExpired())
  {
    screen.SetActivePage(pageBlank);
    screen.CheckRedraw();
  }
}

