#ifndef __WIDGET_H
#define __WIDGET_H

#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ILI9341.h>  //display
#include <Adafruit_FT6206.h>   //touchscreen

#include <TList.h>

// The display uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_FT6206 ctp = Adafruit_FT6206();

//misnomer -- really an action ------ needs to be cleaned up big time
enum Event {NONE, RETURN, INCREMENT, DECREMENT, HOLD_ON, HOLD_OFF, ACTIVATE_COOLING, 
            ACTIVATE_HEATING, ACTIVATE_FAN, DEACTIVATE, COMMIT, MODE_HEAT, MODE_COOL, HOLD_TOGGLE, MODE_CYCLE};

class Widget
{
protected:
  Event action; //Action to respond with -- EEK! This is terrible nomenclature!

public:
  Widget(Event a) {action = a;}
  
  virtual void Draw(void) = 0;
  virtual int IsClicked(int, int) {return 0;}
  virtual void OnClick(void) {}
  virtual void HandleEvent(Event) {}
};

class RectangularWidget : public Widget
{
protected:
  int left, right, top, bottom;
  uint16_t fillColor;
  uint16_t edgeColor; //unused at the moment

public:
  RectangularWidget(int l, int r, int t, int b, Event a, uint16_t fill = ILI9341_BLACK,
   uint16_t edge = ILI9341_BLUE) 
  : Widget(a), left(l), right(r), top(t), bottom(b)
  {  
    fillColor = fill;
    edgeColor = edge;
  }

  void SetAttributes(uint16_t fill, uint16_t edge)
  {
    fillColor = fill;
    edgeColor = edge;
  }
  
  void Draw(void)
  {
    if(fillColor == ILI9341_BLACK) 
      tft.drawRect(left, top, (right - left), (bottom - top), edgeColor);
    else
    {
      tft.fillRect(left, top, (right - left), (bottom - top), fillColor);
      if(fillColor != edgeColor)
        tft.drawRect(left, top, (right - left), (bottom - top), edgeColor);      
    }
  }

  int IsClicked(int x, int y) 
  {
    return (x >= left && x <= right && y >= top && y <= bottom);    
  }
};

class DotWidget : public Widget
{
protected:
  int x, y, radius;
  uint16_t fillColor;
  uint16_t edgeColor; //unused at the moment

public:
  DotWidget(int x_, int y_, int r, Event a) : Widget(a), x(x_), y(y_), radius(r)
  {  
    fillColor = ILI9341_BLACK;
    edgeColor = ILI9341_BLUE;
  }

  void SetAttributes(uint16_t fill, uint16_t edge)
  {
    fillColor = fill;
    edgeColor = edge;
  }
  
  void Draw(void)
  {
    tft.fillCircle(x, y, radius, fillColor);
  }
};

class IndicatorWidget : public DotWidget
{
protected:
  
};

class TextWidget : public RectangularWidget
{
protected:
  uint8_t textSize;
  uint16_t textColor;
  String text;
  
public:
  TextWidget(int l, int r, int t, int b, Event a) : RectangularWidget(l, r, t, b, a)
  {
    textSize = 2;
    textColor = ILI9341_RED;
    RectangularWidget::SetAttributes(ILI9341_BLACK, ILI9341_BLACK);
  }
    
  void SetTextAttributes(uint8_t size, uint16_t color)
  {
    textSize = size;
    textColor = color;
  }

  void Draw(void)
  {
    RectangularWidget::Draw();
    tft.setCursor(left + 5, top);//(top + bottom) / 2 - (7 * textSize) / 2);
    tft.setTextSize(textSize);
    tft.setTextColor(textColor);
    tft.print(text);
  }
};

class CommandWidget : public TextWidget
{
protected:
  Widget* targetWidget;
public:
  CommandWidget(int l, int r, int t, int b, Event act, Widget* target, String displayText) : 
      TextWidget(l, r, t, b, act), targetWidget(target)
  {
    TextWidget::SetAttributes(ILI9341_BLUE, ILI9341_BLUE);
    text = displayText;
  }

  void Draw(void)
  {
    TextWidget::Draw();
  }

  void OnClick(void)
  {
    if(targetWidget)
    {
      targetWidget->HandleEvent(action);
    }
  }
};

class ArrowWidget : public CommandWidget
{
protected:
  //Widget* targetWidget;
  uint16_t triangleColor;
  
public:
  ArrowWidget(int l, int r, int t, int b, Event act, Widget* target, uint16_t color) : 
      CommandWidget(l, r, t, b, act, target, "")
  {
    RectangularWidget::SetAttributes(ILI9341_BLACK, ILI9341_BLACK);
    triangleColor = color;
  }

  void Draw(void)
  {
    RectangularWidget::Draw();
    tft.setCursor(left, top);
    if(action == INCREMENT)
    {
      tft.fillTriangle(left, bottom, right, bottom, (left + right) / 2, top, triangleColor);
    }
    
    if(action == DECREMENT)
    {
      tft.fillTriangle(left, top, right, top, (left + right) / 2, bottom, triangleColor);
    }
  }
};

#define WidgetList TList<Widget*> 
#define WidgetIterator TIListIterator<Widget*> 

#endif
