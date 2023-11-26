#ifndef LETTER_CATCHER_BOUNTY
#define LETTER_CATCHER_BOUNTY

#include "raylib.h"
#include <time.h>

static const char *bountyTexturePath = "resources/bounty.png";
static const int bountyWidth = 50;
static const float bountyMaxSpeed = 5.0f;
static const float bountyAcceleration = 7.0f;
static const float bountyMaxRotation = 20.0f;

typedef struct Bounty {
  Rectangle bounds;
  int horizontalDirection;
  int verticalDirection;
  float horizontalSpeed;
  float verticalSpeed;
  float rotation;
  Texture2D texture;
  clock_t lastRender;
} Bounty;

Bounty *createBounty(Vector2 initialPosition);

void destroyBounty(Bounty *bounty);

void drawBounty(Bounty *bounty);

void processInputForBounty(Bounty *bounty);

#endif