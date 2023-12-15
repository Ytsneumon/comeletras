#include "cutScene.h"
#include <stdio.h>

void initializeCutScene() {
  char frameResource[40];
  for (int i = 1; i < 89; i++) {
    sprintf(frameResource, "resources/ninjasFinalCutscene/%.5d.png", i);
    cutscene[i - 1] = LoadTexture(frameResource);
  }
}

void drawCutScene() {
  BeginDrawing();

  ClearBackground(WHITE);

  clock_t now = clock();
  double elapsedTime = ((double)(now - lastVideoRender)) / CLOCKS_PER_SEC;
  DrawTexturePro(cutscene[framecount], (Rectangle){0, 0, 326, 182}, (Rectangle){0, 143, 900, 502}, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
  if (elapsedTime > 0.0416 && framecount < 88) {
    lastVideoRender = now;
    framecount++;
  }
  if (framecount == 88) {
    framecount = 0;
  }

  EndDrawing();
}