#ifndef LETTER_CATCHER_GAME_UTILS
#define LETTER_CATCHER_GAME_UTILS

#include "raylib.h"

static const int gridSize = 10;

void drawGrid();

void positionRandomly2D(Vector2 *positions, int nElements, int elementWidth, int elementHeight, Rectangle map, int xOffset, int yOffset);

void printRectangleOut(Rectangle rectangle);

void printVector2Out(Vector2 vector);

#endif