
#ifndef LETTER_CATCHER_CUTSCENE
#define LETTER_CATCHER_CUTSCENE

#include "raylib.h"
#include <time.h>

static Texture2D cutscene[88];
static int framecount = 0;
static clock_t lastVideoRender = 0;

void initializeCutScene();

void drawCutScene();

#endif