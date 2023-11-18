#include "assetsData.h"
#include <stdlib.h>

Vector2 *generateMarkerPositions() {
  Vector2 *positions = malloc(sizeof(Vector2) * markerPositionsLength);
  for (int i = 0; i < markerPositionsLength; i++) {
    positions[i] = (Vector2){i * markerFrame.width, 0.0f};
  }
  return positions;
}

Sprite2D *initializeMarker() {
  Sprite2D *marker = createSprite2D(
      markerTextureResourcePath,
      markerFrame,
      generateMarkerPositions(),
      markerPositionsLength,
      markerSequence,
      markerSequenceLength,
      markerInterval);
  return marker;
}

Sprite2D *initializeDragon() {
  Sprite2D *dragon = createSprite2D(
      dragonTextureResourcePath,
      dragonFrame,
      generateMarkerPositions(),
      dragonPositionsLength,
      dragonSequence,
      dragonSequenceLength,
      dragonInterval);
  return dragon;
}

void destroyAsset(Sprite2D *sprite) {
  free(sprite->framePositions);
  destroySprite2D(sprite);
}