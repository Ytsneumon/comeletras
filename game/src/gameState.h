#ifndef LETTER_CATCHER_GAME_STATE
#define LETTER_CATCHER_GAME_STATE

#include "bounty/bounty.h"
#include "raylib.h"
#include "utils/linkedList.h"

typedef struct GameState {
  int currentLetterIndex;
  ListNode *lettersPositions;
  int *wordIndexes;
  int currentWordIndex;
  Bounty *bounty;
} GameState;

#endif