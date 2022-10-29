#pragma once

#include <Arduino.h>

struct Tag
{
  uint16_t id;
  uint8_t rotations; // 0 = N; 1 = E; 2 = S; 3 = W

  uint16_t getPattern(void);
};