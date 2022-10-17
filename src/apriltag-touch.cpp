/*
 * The latest working code.
 * 
 * Need to add a virtual sensor for what the furnace thinks it's doing.
 */

#include "touchscreen.h"
#include <event_timer.h>

Screen screen;

#define DISPLAY_INTERVAL 5000UL
EventTimer timerDisplay;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println(F("Init"));
  
  Wire.begin();
  
  screen.begin();
  screen.clearDisplay();
  screen.display();

  screen.SetupPages();

  timerDisplay.start(2000);
}

void loop() 
{
  delay(2000);
  screen.CheckRedraw();
}

