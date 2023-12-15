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

typedef enum {
  MAIN_MENU,
  GAME,
  CUT_SCENE,
} GameScene;

typedef enum {
  ES,
  DE,
} Language;

#endif