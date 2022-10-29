#pragma once

#include <widget.h>
#include "page.h"

#include <Adafruit_GFX.h>       // Core graphics library
#include <Adafruit_SSD1306.h>   // 128x64 OLED screen

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Screen : public Adafruit_SSD1306
{
private:
  Page* activePage = NULL;
  bool redraw = false;

public:
  Screen(void) : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

  void CheckRedraw(void)
  {
    if(activePage) activePage->Draw();
  }

  void SetActivePage(Page* target) {activePage = target;}
};

extern Screen screen;