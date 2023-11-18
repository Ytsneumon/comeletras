#include "sprite.h"
#include <stdlib.h>

void updateSequenceIndex(Sprite2D *sprite);

Sprite2D *createSprite2D(char *textureResourcePath, Rectangle frame, Vector2 *framePositions, int framePositionsLength, int *sequence, int sequenceLength, double intervalInSeconds) {
  Sprite2D *result = malloc(sizeof(Sprite2D));

  result->texture = LoadTexture(textureResourcePath);
  result->frame = frame;
  result->framePositions = framePositions;
  result->framePositionsLength = framePositionsLength;
  result->sequence = sequence;
  result->sequenceLength = sequenceLength;
  result->intervalInSeconds = intervalInSeconds;
  result->lastRender = 0;
  result->sequenceIndex = 0;

  return result;
}

void destroySprite2D(Sprite2D *sprite) {
  if (sprite != NULL) {
    UnloadTexture(sprite->texture);
    free(sprite);
    sprite = NULL;
  }
}

void drawSprite(Sprite2D *sprite, Rectangle destiny) {
  updateSequenceIndex(sprite);
  Vector2 currentPosition = sprite->framePositions[sprite->sequence[sprite->sequenceIndex]];
  DrawTexturePro(
      sprite->texture,
      (Rectangle){currentPosition.x, currentPosition.y, sprite->frame.width, sprite->frame.height},
      destiny,
      (Vector2){0.0f, 0.0f},
      0.0f,
      WHITE);
}

void drawSpriteNPatch(Sprite2D *sprite, Rectangle destiny, NPatchInfo nPatchInfo) {
  updateSequenceIndex(sprite);
  Vector2 currentPosition = sprite->framePositions[sprite->sequence[sprite->sequenceIndex]];
  Rectangle source = {currentPosition.x, currentPosition.y, sprite->frame.width, sprite->frame.height};

  DrawTextureNPatch(
      sprite->texture,
      (NPatchInfo){
          source,
          nPatchInfo.left,
          nPatchInfo.top,
          nPatchInfo.right,
          nPatchInfo.bottom,
          nPatchInfo.layout},
      destiny,
      (Vector2){0.0f, 0.0f},
      0.0f,
      WHITE);
}

void updateSequenceIndex(Sprite2D *sprite) {
  clock_t now = clock();
  double elapsedTime = ((double)(now - sprite->lastRender)) / CLOCKS_PER_SEC;
  if (elapsedTime > sprite->intervalInSeconds) {
    int missingFrames = elapsedTime / sprite->intervalInSeconds;
    sprite->sequenceIndex = (sprite->sequenceIndex + missingFrames) % sprite->sequenceLength;
    sprite->lastRender = now;
  }
}