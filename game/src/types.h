#ifndef LETTER_CATCHER_TYPES
#define LETTER_CATCHER_TYPES

#include "raylib.h"

typedef struct LetterPosition {
  Rectangle position;
  char letter;
  bool catched;
} LetterPosition;

#endif