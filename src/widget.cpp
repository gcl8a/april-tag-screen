#include <Widget.h>
#include <touchscreen.h>

Widget::Widget(Screen* scr, Action a) {screen = scr; action = a;}

  RectangularWidget::RectangularWidget(Screen* scr, int l, int r, int t, int b, Action a, uint16_t fill,
   uint16_t edge) 
  : Widget(scr, a), left(l), right(r), top(t), bottom(b)
  {  
    fillColor = fill;
    edgeColor = edge;
  }

  void RectangularWidget::SetAttributes(uint16_t fill, uint16_t edge)
  {
    fillColor = fill;
    edgeColor = edge;
  }
  
  void RectangularWidget::Draw(void)
  {
    if(fillColor == COLOR_BLACK) 
      screen->drawRect(left, top, (right - left), (bottom - top), edgeColor);
    else
    {
      screen->fillRect(left, top, (right - left), (bottom - top), fillColor);
      if(fillColor != edgeColor)
        screen->drawRect(left, top, (right - left), (bottom - top), edgeColor);      
    }
  }

  int RectangularWidget::IsClicked(int x, int y) 
  {
    return (x >= left && x <= right && y >= top && y <= bottom);    
  }

void TextWidget::Draw(void)
  {
    RectangularWidget::Draw();
    screen->setCursor(left + 5, top);//(top + bottom) / 2 - (7 * textSize) / 2);
    screen->setTextSize(textSize);
    screen->setTextColor(textColor);
    screen->print(text);
  }