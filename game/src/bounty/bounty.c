#include "bounty.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

// TODO Remove this and give the bounding rect of the space where the bounty can move
static const int headerHeight = 100;

Bounty *createBounty(Vector2 initialPosition) {
  Bounty *bounty = malloc(sizeof(Bounty));
  bounty->texture = LoadTexture(bountyTexturePath);
  bounty->bounds.x = initialPosition.x;
  bounty->bounds.y = initialPosition.y;
  bounty->bounds.width = bountyWidth;
  bounty->bounds.height = bountyWidth;
  bounty->horizontalDirection = 1;
  bounty->verticalDirection = 0;
  bounty->horizontalSpeed = 0.0f;
  bounty->verticalSpeed = 0.0f;
  bounty->rotation = 0.0f;
  return bounty;
}

void destroyBounty(Bounty *bounty) {
  if (bounty != NULL) {
    UnloadTexture(bounty->texture);
    free(bounty);
    bounty = NULL;
  }
}

void drawBounty(Bounty *bounty) {
  Rectangle source = {0, 0, -bounty->horizontalDirection * bounty->texture.width, bounty->texture.height};
  Rectangle destiny = {bounty->bounds.x, bounty->bounds.y, bounty->bounds.width, bounty->bounds.height};
  Vector2 origin = {bounty->bounds.width / 2, bounty->bounds.height / 2};
  DrawTexturePro(bounty->texture, source, destiny, origin, bounty->rotation, WHITE);
  // Rectangle bountyHitbox = {bounty->x - bounty->width / 2, bounty->y - bounty->height / 2, bounty->width, bounty->height};
  //  DrawRectangleLinesEx(bountyHitbox, 1.0f, RED);
}

void processInputForBounty(Bounty *bounty) {
  if (IsKeyDown(KEY_RIGHT)) {
    bounty->horizontalSpeed += bountyAcceleration;
    if (bounty->horizontalSpeed > bountyMaxSpeed) {
      bounty->horizontalSpeed = bountyMaxSpeed;
    }
    bounty->horizontalDirection = 1;
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyDown(KEY_LEFT)) {
    bounty->horizontalSpeed -= bountyAcceleration;
    if (bounty->horizontalSpeed < -bountyMaxSpeed) {
      bounty->horizontalSpeed = -bountyMaxSpeed;
    }
    bounty->horizontalDirection = -1;
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && bounty->horizontalSpeed > 0) {
    bounty->horizontalSpeed -= bountyAcceleration;
    if (bounty->horizontalSpeed < 0) {
      bounty->horizontalSpeed = 0;
    }
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && bounty->horizontalSpeed < 0) {
    bounty->horizontalSpeed += bountyAcceleration;
    if (bounty->horizontalSpeed > 0) {
      bounty->horizontalSpeed = 0;
    }
    bounty->bounds.x += bounty->horizontalSpeed;
  }

  if (IsKeyDown(KEY_DOWN)) {
    bounty->verticalSpeed += bountyAcceleration;
    if (bounty->verticalSpeed > bountyMaxSpeed) {
      bounty->verticalSpeed = bountyMaxSpeed;
    }
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyDown(KEY_UP)) {
    bounty->verticalSpeed -= bountyAcceleration;
    if (bounty->verticalSpeed < -bountyMaxSpeed) {
      bounty->verticalSpeed = -bountyMaxSpeed;
    }
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_DOWN) && !IsKeyDown(KEY_UP) && bounty->verticalSpeed > 0) {
    bounty->verticalSpeed -= bountyAcceleration;
    if (bounty->verticalSpeed < 0) {
      bounty->verticalSpeed = 0;
    }
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_UP) && !IsKeyDown(KEY_DOWN) && bounty->verticalSpeed < 0) {
    bounty->verticalSpeed += bountyAcceleration;
    if (bounty->verticalSpeed > 0) {
      bounty->verticalSpeed = 0;
    }
    bounty->bounds.y += bounty->verticalSpeed;
  }

  if (bounty->verticalSpeed != 0) {
    bounty->rotation = bounty->horizontalDirection * Remap(bounty->verticalSpeed, -bountyMaxSpeed, bountyMaxSpeed, -bountyMaxRotation, bountyMaxRotation);
  } else {
    bounty->rotation = 0;
  }

  if (bounty->rotation > bountyMaxRotation) {
    bounty->rotation = bountyMaxRotation;
  } else if (bounty->rotation < -bountyMaxRotation) {
    bounty->rotation = -bountyMaxRotation;
  }

  if (bounty->bounds.x < bounty->bounds.width / 2)
    bounty->bounds.x = bounty->bounds.width / 2;
  if (bounty->bounds.x > GetScreenWidth() - bounty->bounds.width / 2)
    bounty->bounds.x = GetScreenWidth() - bounty->bounds.width / 2;
  if (bounty->bounds.y < headerHeight + bounty->bounds.height / 2)
    bounty->bounds.y = headerHeight + bounty->bounds.height / 2;
  if (bounty->bounds.y > GetScreenHeight() - bounty->bounds.height / 2)
    bounty->bounds.y = GetScreenHeight() - bounty->bounds.height / 2;
}
