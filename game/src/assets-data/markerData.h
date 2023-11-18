#ifndef LETTER_CATCHER_MARKER_DATA
#define LETTER_CATCHER_MARKER_DATA

#include "assetsData.h"
#include "raylib.h"

static char *markerTextureResourcePath = "resources/marker_sprite.png";
static Rectangle markerFrame = {
    .x = 0.0f,
    .y = 0.0f,
    .width = 32.0f,
    .height = 30.0f,
};
static int markerPositionsLength = 4;
static int markerSequenceLength = 6;
static int markerSequence[6] = {0, 1, 2, 3, 2, 1};
static double markerInterval = 1.0 / 15.0;
static NPatchInfo markerNPatchInfo = {
    .source = (Rectangle){
        .x = 0,
        .y = 0,
        .width = 0,
        .height = 0,
    },
    .left = 16.0f,
    .top = 15.0f,
    .right = 16.0f,
    .bottom = 15.0f,
    .layout = NPATCH_NINE_PATCH};

#endif