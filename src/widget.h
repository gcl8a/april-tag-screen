#ifndef __WIDGET_H
#define __WIDGET_H

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


#include <TList.h>

// // The display uses hardware SPI, plus #9 & #10
// #define TFT_CS 10
// #define TFT_DC 9
// Adafruit_SSD1306 tft = Adafruit_SSD1306(TFT_CS, TFT_DC);
// //Adafruit_FT6206 ctp = Adafruit_FT6206();

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
  RectangularWidget(int l, int r, int t, int b, Event a, uint16_t fill = SSD1306_BLACK,
   uint16_t edge = SSD1306_WHITE) 
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
    if(fillColor == SSD1306_BLACK) 
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
    fillColor = SSD1306_BLACK;
    edgeColor = SSD1306_BLACK;
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
    textColor = SSD1306_WHITE;
    RectangularWidget::SetAttributes(SSD1306_BLACK, SSD1306_BLACK);
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
    TextWidget::SetAttributes(SSD1306_WHITE, SSD1306_BLACK);
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
    RectangularWidget::SetAttributes(SSD1306_BLACK, SSD1306_BLACK);
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
