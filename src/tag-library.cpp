#include "tag-library.h"

// because we're just storing at 16 bit uints, the bitmap starts in the lower right
// and works backwards. That makes the bit shifting work more easily.

uint16_t tags[] = { 0b0010001100011011,
                    0b0010111010100101,
                    0b0011010001101010 };

