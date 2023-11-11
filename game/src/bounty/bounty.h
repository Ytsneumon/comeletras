#ifndef COMELETRAS_BOUNTY
#define COMELETRAS_BOUNTY

#include "raylib.h"

static const char *bountyTexturePath = "resources/bounty.png";
static const int bountyWidth = 50;

typedef struct Bounty {
  Rectangle bounds;
  int horizontalDirection;
  int verticalDirection;
  float horizontalSpeed;
  float verticalSpeed;
  float rotation;
  Texture2D texture;
} Bounty;

Bounty *createBounty(Vector2 initialPosition);

#endif