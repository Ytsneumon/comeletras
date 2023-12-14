#ifndef LETTER_CATCHER_GAME_STATE
#define LETTER_CATCHER_GAME_STATE

#include "bounty/bounty.h"
#include "raylib.h"
#include "types.h"
#include "utils/linkedList.h"

typedef struct GameState {
  int currentLetterIndex;
  ListNode *lettersPositions;
  int *wordIndexes;
  int currentWordIndex;
  Bounty *bounty;
  bool gameFinished;
  GameScene scene;
  Language language;
} GameState;

#endif