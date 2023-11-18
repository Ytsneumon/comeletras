#ifndef LETTER_CATCHER_SPRITE
#define LETTER_CATCHER_SPRITE

#include "raylib.h"
#include <time.h>

typedef struct Sprite2D {
  Texture2D texture;
  Rectangle frame;
  Vector2 *framePositions;
  int framePositionsLength;
  int *sequence;
  int sequenceLength;
  double intervalInSeconds;
  clock_t lastRender;
  int sequenceIndex;
} Sprite2D;

Sprite2D *createSprite2D(char *textureResourcePath, Rectangle frame, Vector2 *framePositions, int framePositionsLength, int *sequence, int sequenceLength, double intervalInSeconds);

void drawSprite(Sprite2D *sprite, Rectangle destiny);

void drawSpriteNPatch(Sprite2D *sprite, Rectangle destiny, NPatchInfo nPatchInfo);

void destroySprite2D(Sprite2D *sprite);

#endif