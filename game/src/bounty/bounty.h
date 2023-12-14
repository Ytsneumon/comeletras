#ifndef LETTER_CATCHER_BOUNTY
#define LETTER_CATCHER_BOUNTY

#include "raylib.h"
#include <time.h>

static const char *bountyTexturePath = "resources/bounty.png";
static const int bountyWidth = 50;
static const float bountyMaxSpeed = 5.0f;
static const float bountyAcceleration = 7.0f;
static const float bountyMaxRotation = 20.0f;
static const int idleAnimationDeltasLength = 14;
static const int idleAnimationDeltas[14] = {0, 1, 2, 3, 3, 2, 1, 0, -1, -2, -3, -3, -2, -1};

enum BountyState {
  IDLE,
  IN_MOVEMENT
};

typedef struct Bounty {
  Rectangle bounds;
  int horizontalDirection;
  int verticalDirection;
  float horizontalSpeed;
  float verticalSpeed;
  float rotation;
  Texture2D texture;
  clock_t lastMovementCalculation;
  clock_t lastRender;
  enum BountyState state;
  int idleAnimationDeltaIndex;
} Bounty;

Bounty *createBounty(Vector2 initialPosition);

void destroyBounty(Bounty *bounty);

void drawBounty(Bounty *bounty);

void processInputForBounty(Bounty *bounty);

#endif