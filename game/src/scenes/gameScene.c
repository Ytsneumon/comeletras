#include "gameScene.h"
#include "../font.h"
#include "../gameState.h"
#include "../main.h"
#include "raylib.h"

void drawBackground() {
  DrawTexture(backgroundTexture, 0, 0, WHITE);
}

void drawCurrentWord(GameState gameState) {
  const char *currentWord = getCurrentWord();
  Vector2 wordDimensions = MeasureTextEx(font, currentWord, font.baseSize, 4);
  Vector2 ribbonPosition = {(GetScreenWidth() / 2) - (wordDimensions.x / 2), 30};

  float marginX = 15.0f;
  float marginY = 10.0f;
  Rectangle ribbonDestiny = {round(ribbonPosition.x - marginX), ribbonPosition.y - marginY, wordDimensions.x + marginX * 2, wordDimensions.y + marginY * 2};
  DrawTextureNPatch(ribbonTexture, ribbonNPatchInfo, ribbonDestiny, (Vector2){0, 0}, 0.0f, WHITE);
  DrawTextEx(font, currentWord, ribbonPosition, font.baseSize, 4, BLACK);

  char letter[2] = "#i";
  sprintf(letter, "%c", currentWord[gameState.currentLetterIndex]);
  char *alreadyCatchedLetters = malloc(sizeof(char) * (gameState.currentLetterIndex + 1));
  strncpy(alreadyCatchedLetters, currentWord, gameState.currentLetterIndex);
  alreadyCatchedLetters[gameState.currentLetterIndex] = '\0';
  Vector2 letterDimensions = MeasureTextEx(font, letter, font.baseSize, 4);
  Vector2 alreadyCatchedLettersDimension = MeasureTextEx(font, alreadyCatchedLetters, font.baseSize, 4);
  marginX = 8.0f;
  Rectangle markerDestiny = {ribbonPosition.x + alreadyCatchedLettersDimension.x - marginX + 4, ribbonPosition.y, letterDimensions.x + marginX * 2, letterDimensions.y};
  drawSpriteNPatch(markerSprite, markerDestiny, markerNPatchInfo);
  free(alreadyCatchedLetters);
}

void drawLeftLetters(GameState gameState) {
  int currentWordLength = strlen(getCurrentWord());
  ListNode *iterator = gameState.lettersPositions;
  int i = 0;
  while (iterator != NULL) {
    LetterPosition *letterPosition = (LetterPosition *)iterator->val;
    if (letterPosition != NULL) {
      char letter[2] = "#i";
      sprintf(letter, "%c", letterPosition->letter);
      DrawTextEx(font, letter, (Vector2){letterPosition->position.x, letterPosition->position.y}, font.baseSize, 4, BLACK);
      Rectangle dragonPosition = {letterPosition->position.x, letterPosition->position.y - 20.0f, 32.0f, 32.0f};
      drawSprite(letterPosition->dragonSprite, dragonPosition);
    }
    iterator = iterator->next;
    i++;
  }
}

void drawGameScene(GameState gameState) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  drawBackground();
  drawCurrentWord(gameState);
  drawLeftLetters(gameState);
  drawBounty(gameState.bounty);

  EndDrawing();
}
