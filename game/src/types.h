#ifndef LETTER_CATCHER_TYPES
#define LETTER_CATCHER_TYPES

#include "raylib.h"
#include "sprite/sprite.h"

typedef struct LetterPosition {
  Rectangle position;
  char letter;
  bool catched;
  Sprite2D *dragonSprite;
} LetterPosition;

enum GameScene {
  MAIN_MENU,
  GAME,
};

#endif