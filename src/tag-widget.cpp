#include <tag-widget.h>
#include <touchscreen.h>

void TagWidget::Draw(void)
  {
    uint16_t pixelSize = (right - left) / 8; // "pixel" here is a tag square

    // white bounding box
    RectangularWidget::Draw();

    //inner layer
    uint16_t leftCorner = left + pixelSize;
    uint16_t topCorner = top + pixelSize;
    
    screen->fillRect(leftCorner, topCorner, pixelSize * 6, pixelSize * 6, COLOR_BLACK);

    leftCorner += pixelSize;
    topCorner += pixelSize;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(pattern[i][j])
            {   
                uint16_t l = leftCorner + j * pixelSize;
                uint16_t t = topCorner + i * pixelSize;
                screen->fillRect(l, t, pixelSize, pixelSize, COLOR_WHITE);
            }
        }
  }