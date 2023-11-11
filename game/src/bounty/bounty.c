#include "bounty.h"

Bounty *createBounty(Vector2 initialPosition) {
  Bounty *bounty = malloc(sizeof(Bounty));
  bounty->texture = LoadTexture(bountyTexturePath);
  bounty->bounds.x = initialPosition.x;
  bounty->bounds.y = initialPosition.y;
  bounty->bounds.width = bountyWidth;
  bounty->bounds.height = bountyWidth;
  return bounty;
}