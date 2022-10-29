#include <Arduino.h>
#include <widget.h>
#include <tag-library.h>

struct Tag
{
  uint16_t id;
  uint8_t rotations; // 0 = N; 1 = E; 2 = S; 3 = W
};

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