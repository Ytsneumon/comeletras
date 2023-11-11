#ifndef COMELETRAS_GAME_STATE
#define COMELETRAS_GAME_STATE

#include "raylib.h"
#include "utils/linkedList.h"

typedef struct GameState {
  int currentLetterIndex;
  ListNode *lettersPositions;
  int *wordIndexes;
  int currentWordIndex;
  Rectangle bounty;
  int bountyHorizontalDirection;
  int bountyVerticalDirection;
  float bountyHorizontalSpeed;
  float bountyVerticalSpeed;
  float bountyRotation;
  int currentFrame;
  int framesCounter;
  int framesSpeed;
} GameState;

#endif