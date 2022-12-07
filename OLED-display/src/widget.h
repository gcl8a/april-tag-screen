#ifndef __WIDGET_H
#define __WIDGET_H

#include <TList.h>
#include <Adafruit_SSD1306.h>   // for the colors...needs a better way

#define COLOR_WHITE SSD1306_WHITE
#define COLOR_BLACK SSD1306_BLACK

enum Action {NONE, RETURN, INCREMENT, DECREMENT, HOLD_ON, HOLD_OFF, ACTIVATE_COOLING, 
            ACTIVATE_HEATING, ACTIVATE_FAN, DEACTIVATE, COMMIT, MODE_HEAT, MODE_COOL, HOLD_TOGGLE, MODE_CYCLE};

class Screen;

class Widget
{
protected:
  Screen* screen = NULL;
  Action action; //Action to respond with -- EEK! This is terrible nomenclature!

public:
  Widget(Screen* scr, Action a);
  
  virtual void Draw(void) = 0;
  virtual int IsClicked(int, int) {return 0;}
  virtual void OnClick(void) {}
  virtual void HandleEvent(Action) {}
};

class RectangularWidget : public Widget
{
protected:
  int left, right, top, bottom;
  uint16_t fillColor;
  uint16_t edgeColor; //unused at the moment

public:
  RectangularWidget(Screen* scr, int l, int r, int t, int b, Action a, uint16_t fill = COLOR_BLACK,
   uint16_t edge = COLOR_WHITE);

  void SetAttributes(uint16_t fill, uint16_t edge);  
  void Draw(void);
  int IsClicked(int x, int y);
};

// class DotWidget : public Widget
// {
// protected:
//   int x, y, radius;
//   uint16_t fillColor;
//   uint16_t edgeColor; //unused at the moment

// public:
//   DotWidget(Screen* scr, int x_, int y_, int r, Event a) : Widget(scr, a), x(x_), y(y_), radius(r)
//   {  
//     fillColor = SSD1306_BLACK;
//     edgeColor = SSD1306_BLACK;
//   }

//   void SetAttributes(uint16_t fill, uint16_t edge)
//   {
//     fillColor = fill;
//     edgeColor = edge;
//   }
  
//   void Draw(void)
//   {
//     screen->fillCircle(x, y, radius, fillColor);
//   }
// };

class TextWidget : public RectangularWidget
{
protected:
  uint8_t textSize;
  uint16_t textColor;
  String text;
  
public:
  TextWidget(Screen* scr, int l, int r, int t, int b, Action a) : RectangularWidget(scr, l, r, t, b, a)
  {
    textSize = 2;
    textColor = COLOR_WHITE;
    RectangularWidget::SetAttributes(COLOR_BLACK, COLOR_BLACK);
  }
    
  void SetTextAttributes(uint8_t size, uint16_t color)
  {
    textSize = size;
    textColor = color;
  }

  void Draw(void);
};

// class CommandWidget : public TextWidget
// {
// protected:
//   Widget* targetWidget;
// public:
//   CommandWidget(Screen* scr, int l, int r, int t, int b, Event act, Widget* target, String displayText) : 
//       TextWidget(scr, l, r, t, b, act), targetWidget(target)
//   {
//     TextWidget::SetAttributes(COLOR_WHITE, COLOR_BLACK);
//     text = displayText;
//   }

//   void Draw(void)
//   {
//     TextWidget::Draw();
//   }

//   void OnClick(void)
//   {
//     if(targetWidget)
//     {
//       targetWidget->HandleEvent(action);
//     }
//   }
// };

// class ArrowWidget : public CommandWidget
// {
// protected:
//   //Widget* targetWidget;
//   uint16_t triangleColor;
  
// public:
//   ArrowWidget(Screen* scr, int l, int r, int t, int b, Event act, Widget* target, uint16_t color) : 
//       CommandWidget(scr, l, r, t, b, act, target, "")
//   {
//     RectangularWidget::SetAttributes(COLOR_BLACK, COLOR_BLACK);
//     triangleColor = color;
//   }

//   void Draw(void)
//   {
//     RectangularWidget::Draw();
//     screen->setCursor(left, top);
//     if(action == INCREMENT)
//     {
//       screen->fillTriangle(left, bottom, right, bottom, (left + right) / 2, top, triangleColor);
//     }
    
//     if(action == DECREMENT)
//     {
//       screen->fillTriangle(left, top, right, top, (left + right) / 2, bottom, triangleColor);
//     }
//   }
// };

#define WidgetList TList<Widget*> 
#define WidgetIterator TIListIterator<Widget*> 

#endif
