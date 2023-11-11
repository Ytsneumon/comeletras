#include "bounty.h"
#include <stdio.h>
#include <stdlib.h>

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
