#include <Arduino.h>
#include <widget.h>

class TagWidget : public RectangularWidget
{
protected:
  uint8_t tagID;
  uint8_t pattern[4][4] = {0};

public:
  TagWidget(int l, int r, int t, int b, uint8_t id) 
      : RectangularWidget(l, r, t, b, NONE, ILI9341_WHITE, ILI9341_WHITE), tagID(id)
  {
        pattern[0][2] = 1;
        pattern[1][2] = 1;
        pattern[1][3] = 1;
        pattern[2][3] = 1;
        pattern[3][0] = 1;
        pattern[3][2] = 1;
        pattern[3][3] = 1;
  }
    
  void Draw(void)
  {
    uint16_t pixelSize = (right - left) / 8; // "pixel" here is a tag square

    // white bounding box
    RectangularWidget::Draw();

    //inner layer
    uint16_t leftCorner = left + pixelSize;
    uint16_t topCorner = top + pixelSize;
    
    tft.fillRect(leftCorner, topCorner, pixelSize * 6, pixelSize * 6, ILI9341_BLACK);

    leftCorner += pixelSize;
    topCorner += pixelSize;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(pattern[i][j])
            {   
                uint16_t l = leftCorner + j * pixelSize;
                uint16_t t = topCorner + i * pixelSize;
                tft.fillRect(l, t, pixelSize, pixelSize, ILI9341_WHITE);
            }
        }

  }

  void OnClick(void)
  {
    //if(action == RETURN) activePage = target;
  }
};