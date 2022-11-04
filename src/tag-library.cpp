#include "tag-library.h"

// because we're just storing at 16 bit uints, the bitmap starts in the lower right
// and works backwards. That makes the bit shifting work more easily.

// I started typing them out in binary, but then I found the hex values below...
//
// uint16_t tags[] = { 0b0010001100011011,
//                     0b0010111010100101,
//                     0b0011010001101010 };

const uint16_t tags[] =
  { 0x231b, 0x2ea5, 0x346a, 0x45b9, 0x79a6, 0x7f6b, 0xb358, 0xe745, 0xfe59, 0x156d, 
    0x380b, 0xf0ab, 0x0d84, 0x4736, 0x8c72, 0xaf10, 0x093c, 0x93b4, 0xa503, 0x468f, 
    0xe137, 0x5795, 0xdf42, 0x1c1d, 0xe9dc, 0x73ad, 0xad5f, 0xd530, 0x07ca, 0xaf2e };

uint16_t Tag::getPattern(void)
{
    if(id >= 0 && id < 30) return tags[id];
    else return 0;
}
