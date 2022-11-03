/*
 * The latest working code.
 * 
 * Need to add a virtual sensor for what the furnace thinks it's doing.
 */

#include "touchscreen.h"
#include <event_timer.h>
#include <tag-widget.h>
#include <tag-library.h>
#include <button.h>
#include <keypad.h>

Screen screen;

#define DISPLAY_INTERVAL 2000UL
#define REFRESH_INTERVAL 5000UL

EventTimer timerDisplay;

Page* pageBlank = new Page(&screen);
Page* pageTag = new Page(&screen);

Tag tag;

Button button(A2);

Metal32340SWKeypad keypad;
String code;

void handleKeyPress(uint8_t key)
{
  if(key == POUND)
  {
    if(code.length() == 3)
    {
      tag.id = code.substring(0, 2).toInt();
      tag.rotations = code.substring(2).toInt();

      Serial.print(tag.id);
      Serial.print('\t');
      Serial.print(tag.rotations);
      Serial.print('\n');

      screen.SetActivePage(pageTag);
      screen.CheckRedraw();
      timerDisplay.Start(DISPLAY_INTERVAL);

    }
    code = "";
  }

  else if(key == STAR)
  {
      screen.SetActivePage(pageTag);
      screen.CheckRedraw();
      timerDisplay.Start(DISPLAY_INTERVAL);
  }

  else if(key == 10) code += "0";

  else code += String(key);

  Serial.println(code); //for debugging

  
}

void SetupPages(void)
{
    Serial.println(F("SetupPages"));

    tag.id = 1;
    tag.rotations = 0;

    pageTag->AddWidget(new TagWidget(&screen, 32, 96, 0, 64, &tag));
    pageBlank->AddWidget(new RectangularWidget(&screen, 32, 96, 0, 64, NONE));
    
    button.init();

    Serial.println(F("/SetupPages"));
}

void setup(void) 
{
  Serial.begin(115200);

  Serial.println(F("Init"));
  
  Wire.begin();
  
  screen.begin();

  delay(10);

  screen.clearDisplay();
  screen.display();

  SetupPages();
}

void loop() 
{
  if(button.checkButtonPress())
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

  uint8_t key = keypad.checkKeypress();
  if(key) handleKeyPress(key);
}

