#ifndef LETTER_CATCHER_MAIN
#define LETTER_CATCHER_MAIN

#include "assets-data/assetsData.h"
#include "bounty/bounty.h"
#include "font.h"
#include "gameState.h"
#include "raylib.h"
#include "raymath.h"
#include "sprite/sprite.h"
#include "types.h"
#include "utils/commonUtils.h"
#include "utils/gameUtils.h"
#include "utils/linkedList.h"
#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void UpdateDrawFrame(void);
void initiliaze();
void initializeCurrentWord();
void processInput();
void interactions();
void drawBackground();
void drawCurrentWord();
void drawLeftLetters();
void printLettersPositions();
Vector2 getInitialPoint();
char *getCurrentWord();
void initializeLettersPositions(GameState *gameState, Vector2 *positions, char *letters, int length);

#endif