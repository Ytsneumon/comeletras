#include "gameUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void drawGrid() {
  int width = GetScreenWidth();
  int height = GetScreenHeight();
  int redLineCounter = 1;

  for (int i = gridSize; i < width; i += gridSize) {
    if (redLineCounter == 5) {
      redLineCounter = 0;
      DrawLine(i, 0, i, height, RED);
    } else {
      DrawLine(i, 0, i, height, GRAY);
    }
    redLineCounter++;
  }
  redLineCounter = 1;
  for (int j = gridSize; j < height; j += gridSize) {
    if (redLineCounter == 5) {
      redLineCounter = 0;
      DrawLine(0, j, width, j, RED);
    } else {
      DrawLine(0, j, width, j, GRAY);
    }
    redLineCounter++;
  }
}

void positionRandomly2D(Vector2 *positions, int nElements, int elementWidth, int elementHeight, Rectangle map, int xOffset, int yOffset) {
  srand(time(NULL));
  int xSpaces = map.width / elementWidth;
  int ySpaces = map.height / elementHeight;
  int totalSpaces = xSpaces * ySpaces;
  bool *spaces = malloc(sizeof(bool) * totalSpaces);
  memset(spaces, false, totalSpaces);
  if (nElements < totalSpaces) {
    int i = 0;
    while (i < nElements) {
      int spaceCandidate = rand() % totalSpaces;
      if (!spaces[spaceCandidate]) {
        positions[i].x = ((spaceCandidate % ySpaces) * elementWidth) + map.x + xOffset;
        positions[i].y = ((spaceCandidate / xSpaces) * elementHeight) + map.y + yOffset;
        spaces[spaceCandidate] = true;
        i++;
      }
    }
  }
}

void printRectangleOut(Rectangle rectangle) {
  printf("Rectangle { x: %.2f, y: %.2f, width: %.2f, height: %.2f }\n", rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void printVector2Out(Vector2 vector) {
  printf("Vector2 { x: %.2f, y: %.2f }\n", vector.x, vector.y);
}
