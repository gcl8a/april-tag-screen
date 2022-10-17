#include <Arduino.h>
#include <widget.h>

class TagWidget : public RectangularWidget
{
protected:
  uint8_t tagID;
  uint8_t pattern[4][4] = {0};

public:
  TagWidget(Screen* scr, int l, int r, int t, int b, uint8_t id) 
      : RectangularWidget(scr, l, r, t, b, NONE, COLOR_WHITE, COLOR_WHITE), tagID(id)
  {
        pattern[0][2] = 1;
        pattern[1][2] = 1;
        pattern[1][3] = 1;
        pattern[2][3] = 1;
        pattern[3][0] = 1;
        pattern[3][2] = 1;
        pattern[3][3] = 1;
  }
    
  void Draw(void);
};