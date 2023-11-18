#ifndef LETTER_CATCHER_DRAGON_DATA
#define LETTER_CATCHER_DRAGON_DATA

#include "assetsData.h"
#include "raylib.h"

static char *dragonTextureResourcePath = "resources/ViridianDrakeIdleSide.png";
static Rectangle dragonFrame = {
    .x = 0.0f,
    .y = 0.0f,
    .width = 16.0f,
    .height = 16.0f,
};
static int dragonPositionsLength = 4;
static int dragonSequenceLength = 4;
static int dragonSequence[4] = {0, 1, 2, 3};
static double dragonInterval = 1.0 / 5.0;

#endif