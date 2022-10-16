#ifndef __TOUCHSCREEN_H
#define __TOUCHSCREEN_H

#include <widget.h>
#include "tag-widget.h"

uint8_t redraw = false;

class Page
{
protected:
  WidgetList widgets;

public:
  Page(void) {}
  
  void Draw(void)
  {
    tft.fillScreen(SSD1306_BLACK);

    WidgetIterator widgetIter(widgets);
    while(widgetIter.Current())
    {
      widgetIter.Current()->Draw();
      widgetIter++;
    }
  }  

  void AddWidget(Widget* widget)
  {
    widgets.Add(widget);
  }

  int HandleClick(int x, int y)
  {
    int retVal = 0;
    WidgetIterator widgetIter(widgets);
    while(widgetIter.Current())
    {
      if(widgetIter.Current()->IsClicked(x,y)) 
      {
        widgetIter.Current()->OnClick();
        retVal = 1;
      }
      widgetIter++;
    }

    return retVal;
  }
};

Page* activePage = NULL;

class PageWidget : public TextWidget
{
protected:
  String displayText;
  Page* target;
public:
  PageWidget(int l, int r, int t, int b, Event act, Page* p, String text) 
      : TextWidget(l, r, t, b, act), displayText(text), target(p)
  {
  }
    
  void Draw(void)
  {
    TextWidget::Draw();
    tft.print(displayText);
  }

  void OnClick(void)
  {
    if(action == RETURN) activePage = target;
  }
};

Page* pageHome = new Page;
Page* pageTag = new Page;

Page* SetupPages(void)
{
  Serial.println(F("SetupPages"));

  Serial.println(F("/pages"));
  pageTag->AddWidget(new TagWidget(32, 96, 0, 64, 1));
  Serial.println(F("/pageHome"));

  Serial.println(F("/SetupPages"));

  return pageTag;
}

#endif
