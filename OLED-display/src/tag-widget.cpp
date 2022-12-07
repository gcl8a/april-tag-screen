#include <tag-widget.h>
#include <touchscreen.h>

uint16_t moveBit(const uint16_t& p, int8_t from, int8_t to)
{
    uint16_t mask = 1 << from;
    int8_t distance = to - from;
    uint16_t r = distance < 0 ? (p & mask) >> -distance : (p & mask) << distance;

    return r;
}

uint16_t rotateTag(const uint16_t& pattern)
{
    uint16_t newPattern = 0;

    newPattern |= moveBit(pattern, 0, 3);
    newPattern |= moveBit(pattern, 1, 7);
    newPattern |= moveBit(pattern, 2, 11);
    newPattern |= moveBit(pattern, 3, 15);
    newPattern |= moveBit(pattern, 4, 2);
    newPattern |= moveBit(pattern, 5, 6);
    newPattern |= moveBit(pattern, 6, 10);
    newPattern |= moveBit(pattern, 7, 14);
    newPattern |= moveBit(pattern, 8, 1);
    newPattern |= moveBit(pattern, 9, 5);
    newPattern |= moveBit(pattern, 10, 9);
    newPattern |= moveBit(pattern, 11, 13);
    newPattern |= moveBit(pattern, 12, 0);
    newPattern |= moveBit(pattern, 13, 4);
    newPattern |= moveBit(pattern, 14, 8);
    newPattern |= moveBit(pattern, 15, 12);

    return newPattern;
}

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

    if(!currTag) 
    {
        Serial.println("No valid tag.");
        return;
    }

    uint16_t pattern = currTag->getPattern();

    Serial.println(pattern, BIN);

    for(int i = 0; i < currTag->rotations; i++)
    {
        pattern = rotateTag(pattern);
    }

    Serial.println(pattern, BIN);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            int index = i * 4 + j;
            if((pattern >> index) & 1)
            {   
                uint16_t l = leftCorner + j * pixelSize;
                uint16_t t = topCorner + i * pixelSize;
                screen->fillRect(l, t, pixelSize, pixelSize, COLOR_WHITE);
            }
        }
    //currTag->rotations++; uncomment to test
  }