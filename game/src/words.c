#include "words.h"
#include "utils/commonUtils.h"
#include <stdlib.h>

void initializeWords(GameState *gameState) {
  gameState->wordIndexes = malloc(sizeof(int) * NUMBER_OF_WORDS);
  initializeNumberArrayWithValue(gameState->wordIndexes, NUMBER_OF_WORDS, -1);
  int i = 0;
  while (i < NUMBER_OF_WORDS) {
    int wordIndex = rand() % NUMBER_OF_WORDS;
    if (!contains(gameState->wordIndexes, wordIndex, NUMBER_OF_WORDS)) {
      gameState->wordIndexes[i] = wordIndex;
      i++;
    }
  }
}
