#ifndef LETTER_CATCHER_MAIN
#define LETTER_CATCHER_MAIN

#include "assets-data/assetsData.h"
#include "bounty/bounty.h"
#include "cutScene/cutScene.h"
#include "font.h"
#include "gameState.h"
#include "raylib.h"
#include "raymath.h"
#include "scenes/gameScene.h"
#include "scenes/mainMenu.h"
#include "sprite/sprite.h"
#include "types.h"
#include "utils/commonUtils.h"
#include "utils/gameUtils.h"
#include "utils/linkedList.h"
#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern Texture2D backgroundTexture;
extern Texture2D ribbonTexture;
extern Texture2D esFlag;
extern Texture2D deFlag;
extern Sprite2D *markerSprite;

void UpdateDrawFrame(void);
void initiliaze();
void initializeCurrentWord();
void processInput();
void interactions();
void printLettersPositions();
Vector2 getInitialPoint();
char *getCurrentWord();
void initializeLettersPositions(GameState *gameState, Vector2 *positions, char *letters, int length);
void nextWord();
void processInputForMainMenu();

#endif