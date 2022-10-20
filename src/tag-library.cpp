#include "tag-library.h"

uint16_t tags[] = { 0b0010001100011011,
                    0b0010111010100101,
                    0b0011010001101010 };


uint16_t getTag(uint8_t id)
{
    return tags[id];
}

