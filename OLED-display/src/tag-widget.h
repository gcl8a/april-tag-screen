#include <Arduino.h>
#include <widget.h>
#include <tag-library.h>


class TagWidget : public RectangularWidget
{
protected:
  Tag* currTag = NULL;

public:
  TagWidget(Screen* scr, int l, int r, int t, int b, Tag* pTag) 
      : RectangularWidget(scr, l, r, t, b, NONE, COLOR_WHITE, COLOR_WHITE), currTag(pTag)
  {}
    
  void Draw(void);
};