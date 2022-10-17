#pragma once

#include <widget.h>

class Screen;

class Page
{
protected:
  Screen* screen = NULL;
  WidgetList widgets;

public:
  Page(Screen* scr) {screen = scr;}
  
  void Draw(void);
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

class PageWidget : public TextWidget
{
protected:
  String displayText;
  Page* target;
public:
  PageWidget(Screen* scr, int l, int r, int t, int b, Action act, Page* p, String text) 
      : TextWidget(scr, l, r, t, b, act), displayText(text), target(p)
  {
  }
    
  void Draw(void);
  void OnClick(void);
};
