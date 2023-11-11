#ifndef COMELETRAS_TYPES
#define COMELETRAS_TYPES

#include "raylib.h"

typedef struct LetterPosition {
  Rectangle position;
  char letter;
  bool catched;
} LetterPosition;

#endif