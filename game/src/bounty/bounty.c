#include "bounty.h"
#include "raymath.h"
#include <stdbool.h>
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

void clampBountyPosition(Bounty *bounty) {
  float clampedValue = Clamp(bounty->bounds.x, bounty->bounds.width / 2, GetScreenWidth() - bounty->bounds.width / 2);
  if (clampedValue != bounty->bounds.x) {
    bounty->bounds.x = clampedValue;
    bounty->horizontalSpeed = 0.0f;
  }
  clampedValue = Clamp(bounty->bounds.y, headerHeight + bounty->bounds.height / 2, GetScreenHeight() - bounty->bounds.height / 2);
  if (clampedValue != bounty->bounds.y) {
    bounty->bounds.y = clampedValue;
    bounty->verticalSpeed = 0.0f;
  }
}

void processInputForBounty(Bounty *bounty) {
  clock_t now = clock();
  double elapsedTime = ((double)(now - bounty->lastRender)) / CLOCKS_PER_SEC;
  bounty->lastRender = now;
  if (IsKeyDown(KEY_RIGHT)) {
    bounty->horizontalSpeed = Clamp(bounty->horizontalSpeed + bountyAcceleration * elapsedTime, -bountyMaxSpeed, bountyMaxSpeed);
    bounty->horizontalDirection = 1;
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyDown(KEY_LEFT)) {
    bounty->horizontalSpeed = Clamp(bounty->horizontalSpeed - bountyAcceleration * elapsedTime, -bountyMaxSpeed, bountyMaxSpeed);
    bounty->horizontalDirection = -1;
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && bounty->horizontalSpeed > 0) {
    bounty->horizontalSpeed = Clamp(bounty->horizontalSpeed - bountyAcceleration * elapsedTime, 0.0f, bountyMaxSpeed);
    bounty->bounds.x += bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && bounty->horizontalSpeed < 0) {
    bounty->horizontalSpeed = Clamp(bounty->horizontalSpeed + bountyAcceleration * elapsedTime, -bountyMaxSpeed, 0.0f);
    bounty->bounds.x += bounty->horizontalSpeed;
  }

  if (IsKeyDown(KEY_DOWN)) {
    bounty->verticalSpeed = Clamp(bounty->verticalSpeed + bountyAcceleration * elapsedTime, -bountyMaxSpeed, bountyMaxSpeed);
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyDown(KEY_UP)) {
    bounty->verticalSpeed = Clamp(bounty->verticalSpeed - bountyAcceleration * elapsedTime, -bountyMaxSpeed, bountyMaxSpeed);
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_DOWN) && !IsKeyDown(KEY_UP) && bounty->verticalSpeed > 0) {
    bounty->verticalSpeed = Clamp(bounty->verticalSpeed - bountyAcceleration * elapsedTime, 0.0f, bountyMaxSpeed);
    bounty->bounds.y += bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_UP) && !IsKeyDown(KEY_DOWN) && bounty->verticalSpeed < 0) {
    bounty->verticalSpeed = Clamp(bounty->verticalSpeed + bountyAcceleration * elapsedTime, -bountyMaxSpeed, 0.0f);
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

  clampBountyPosition(bounty);
}
