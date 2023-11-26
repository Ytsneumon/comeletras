#ifndef LETTER_CATCHER_ASSETS_DATA
#define LETTER_CATCHER_ASSETS_DATA

#include "../sprite/sprite.h"
#include "dragonData.h"
#include "markerData.h"
#include "raylib.h"

static NPatchInfo ribbonNPatchInfo = {
    (Rectangle){
        65.0f,
        225.0f,
        62.0f,
        30.0f},
    31.0f,
    15.0f,
    31.0f,
    15.0f,
    NPATCH_NINE_PATCH};

static Sprite2D *dragonSprites[N_DRAGONS];

Sprite2D *initializeMarker();
Sprite2D *initializeDragon(int dragonIndex);

void destroyAsset(Sprite2D *sprite);

#endif