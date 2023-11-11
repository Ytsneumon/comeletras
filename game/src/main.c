#include "bounty/bounty.h"
#include "font.h"
#include "gameState.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"
#include "utils/commonUtils.h"
#include "utils/gameUtils.h"
#include "utils/linkedList.h"
#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions declarations
static void UpdateDrawFrame(void);
static void initiliaze();
static void initializeWords();
static void initializeCurrentWord();
static void processInput();
static void interactions();
static void drawBackground();
static void drawCurrentWord();
static void drawLeftLetters();
static void printLettersPositions();
const char *getCurrentWord();
static Vector2 getInitialPoint();

// Constants
static const int screenWidth = 900;
static const int screenHeight = 900;

static const int headerHeight = 100;
static const int letterWidth = 50;
static const int letterHeight = 50;
static const float bountyMaxSpeed = 5.0f;
static const float bountyAcceleration = .2f;
static const float bountyMaxRotation = 20.0f;

static GameState gameState = {
    .currentLetterIndex = 0,
    .currentWordIndex = 0,
    .currentFrame = 0,
    .framesCounter = 0,
    .framesSpeed = 8,
};

// Textures
Texture2D ribbonTexture;
Texture2D backgroundTexture;
Texture2D markerSprite;
Texture2D dragonSprite;

int main(void) {
  initiliaze();
  while (!WindowShouldClose()) {
    gameState.framesCounter++;
    if (gameState.framesCounter >= (60 / gameState.framesSpeed)) {
      gameState.framesCounter = 0;
      gameState.currentFrame++;

      if (gameState.currentFrame > 3)
        gameState.currentFrame = 0;
    }

    processInput();
    interactions();
    UpdateDrawFrame();
  }

  destroyBounty(gameState.bounty);

  UnloadTexture(ribbonTexture);
  UnloadTexture(backgroundTexture);
  UnloadTexture(markerSprite);
  UnloadTexture(dragonSprite);

  CloseWindow();

  return 0;
}

// TODO: Move bounty data to a struct and related functions to a separate file
// TODO: Generalize movements and move it to a separate file
// TODO: Draw clouds
// TODO: Draw letters floating balloons
// TODO: Effects and sound when a letter is catched or the word/game is finished

static void initiliaze() {
  InitWindow(screenWidth, screenHeight, "Letter Catcher");
  SetTargetFPS(60);
  initializeFont();
  initializeWords();
  initializeCurrentWord();
  gameState.bounty = createBounty(getInitialPoint());
  backgroundTexture = LoadTexture("resources/clouds_background.png");
  markerSprite = LoadTexture("resources/marker_sprite.png");
  dragonSprite = LoadTexture("resources/ViridianDrakeIdleSide.png");
}

static void UpdateDrawFrame(void) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  // drawGrid();
  drawBackground();
  drawCurrentWord();
  drawLeftLetters();
  drawBounty(gameState.bounty);

  EndDrawing();
}

static void initializeWords() {
  ribbonTexture = LoadTexture("resources/ribbons.png");
  gameState.wordIndexes = malloc(sizeof(int) * NUMBER_OF_WORDS);
  initializeNumberArrayWithValue(gameState.wordIndexes, NUMBER_OF_WORDS, -1);
  int i = 0;
  while (i < NUMBER_OF_WORDS) {
    int wordIndex = rand() % NUMBER_OF_WORDS;
    if (!contains(gameState.wordIndexes, wordIndex, NUMBER_OF_WORDS)) {
      gameState.wordIndexes[i] = wordIndex;
      i++;
    }
  }
}

static void initializeCurrentWord() {
  gameState.currentLetterIndex = 0;
  const char *currentWord = getCurrentWord();
  int currentWordLength = strlen(currentWord);
  Vector2 *positions = malloc(currentWordLength * sizeof(Vector2));
  Rectangle map = {0, headerHeight, GetScreenWidth(), GetScreenHeight() - headerHeight};
  positionRandomly2D(positions, currentWordLength, letterWidth, letterHeight, map, 11, 5);
  gameState.lettersPositions = NULL;
  for (int i = 0; i < currentWordLength; i++) {
    LetterPosition *letterPosition = malloc(sizeof(LetterPosition));
    letterPosition->position = (Rectangle){positions[i].x, positions[i].y, 50, 50};
    letterPosition->catched = false;
    letterPosition->letter = currentWord[i];
    gameState.lettersPositions = addElement(gameState.lettersPositions, letterPosition);
  }
  free(positions);
}

static void drawCurrentWord() {
  const char *currentWord = getCurrentWord();
  Vector2 wordDimensions = MeasureTextEx(font, currentWord, font.baseSize, 4);
  Vector2 position = {(GetScreenWidth() / 2) - (wordDimensions.x / 2), 30};

  float marginX = 15.0f;
  float marginY = 10.0f;
  Rectangle ribbonDestiny = {round(position.x - marginX), position.y - marginY, wordDimensions.x + marginX * 2, wordDimensions.y + marginY * 2};
  NPatchInfo ribbon9PatchInfo = {(Rectangle){65.0f, 225.0f, 62.0f, 30.0f}, 31.0f, 15.0f, 31.0f, 15.0f, NPATCH_NINE_PATCH};
  DrawTextureNPatch(ribbonTexture, ribbon9PatchInfo, ribbonDestiny, (Vector2){0, 0}, 0.0f, WHITE);

  DrawTextEx(font, currentWord, position, font.baseSize, 4, BLACK);

  char letter[2] = "#i";
  sprintf(letter, "%c", currentWord[gameState.currentLetterIndex]);
  char *alreadyCatchedLetters = malloc(sizeof(char) * (gameState.currentLetterIndex + 1));
  strncpy(alreadyCatchedLetters, currentWord, gameState.currentLetterIndex);
  alreadyCatchedLetters[gameState.currentLetterIndex] = '\0';

  // Inputs
  Vector2 letterDimensions = MeasureTextEx(font, letter, font.baseSize, 4);
  Vector2 alreadyCatchedLettersDimension = MeasureTextEx(font, alreadyCatchedLetters, font.baseSize, 4);
  marginX = 8.0f;
  Rectangle markerDestiny = {position.x + alreadyCatchedLettersDimension.x - marginX + 4, position.y, letterDimensions.x + marginX * 2, letterDimensions.y};

  // Nine patch and sprite logic
  NPatchInfo marker9PatchInfo = {(Rectangle){gameState.currentFrame * 32.0f, 0.0f, 32.0f, 30.0f}, 16.0f, 15.0f, 16.0f, 15.0f, NPATCH_NINE_PATCH};
  DrawTextureNPatch(markerSprite, marker9PatchInfo, markerDestiny, (Vector2){0, 0}, 0.0f, WHITE);
  free(alreadyCatchedLetters);
}

static void drawLeftLetters() {
  int currentWordLength = strlen(getCurrentWord());
  ListNode *iterator = gameState.lettersPositions;
  int i = 0;
  while (iterator != NULL) {
    LetterPosition *letterPosition = (LetterPosition *)iterator->val;
    if (letterPosition != NULL) {
      char letter[2] = "#i";
      sprintf(letter, "%c", letterPosition->letter);
      DrawTextEx(font, letter, (Vector2){letterPosition->position.x, letterPosition->position.y}, font.baseSize, 4, BLACK);
      Rectangle dragonSource = {16.0f * gameState.currentFrame, 0, 16.0f, 16.0f};
      Rectangle dragonPosition = {letterPosition->position.x, letterPosition->position.y - 20.0f, 32.0f, 32.0f};
      DrawTexturePro(dragonSprite, dragonSource, dragonPosition, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    }
    iterator = iterator->next;
    i++;
  }
}

static void processInput() {
  if (IsKeyDown(KEY_RIGHT)) {
    gameState.bounty->horizontalSpeed += bountyAcceleration;
    if (gameState.bounty->horizontalSpeed > bountyMaxSpeed) {
      gameState.bounty->horizontalSpeed = bountyMaxSpeed;
    }
    gameState.bounty->horizontalDirection = 1;
    gameState.bounty->bounds.x += gameState.bounty->horizontalSpeed;
  } else if (IsKeyDown(KEY_LEFT)) {
    gameState.bounty->horizontalSpeed -= bountyAcceleration;
    if (gameState.bounty->horizontalSpeed < -bountyMaxSpeed) {
      gameState.bounty->horizontalSpeed = -bountyMaxSpeed;
    }
    gameState.bounty->horizontalDirection = -1;
    gameState.bounty->bounds.x += gameState.bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && gameState.bounty->horizontalSpeed > 0) {
    gameState.bounty->horizontalSpeed -= bountyAcceleration;
    if (gameState.bounty->horizontalSpeed < 0) {
      gameState.bounty->horizontalSpeed = 0;
    }
    gameState.bounty->bounds.x += gameState.bounty->horizontalSpeed;
  } else if (IsKeyUp(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && gameState.bounty->horizontalSpeed < 0) {
    gameState.bounty->horizontalSpeed += bountyAcceleration;
    if (gameState.bounty->horizontalSpeed > 0) {
      gameState.bounty->horizontalSpeed = 0;
    }
    gameState.bounty->bounds.x += gameState.bounty->horizontalSpeed;
  }

  if (IsKeyDown(KEY_DOWN)) {
    gameState.bounty->verticalSpeed += bountyAcceleration;
    if (gameState.bounty->verticalSpeed > bountyMaxSpeed) {
      gameState.bounty->verticalSpeed = bountyMaxSpeed;
    }
    gameState.bounty->bounds.y += gameState.bounty->verticalSpeed;
  } else if (IsKeyDown(KEY_UP)) {
    gameState.bounty->verticalSpeed -= bountyAcceleration;
    if (gameState.bounty->verticalSpeed < -bountyMaxSpeed) {
      gameState.bounty->verticalSpeed = -bountyMaxSpeed;
    }
    gameState.bounty->bounds.y += gameState.bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_DOWN) && !IsKeyDown(KEY_UP) && gameState.bounty->verticalSpeed > 0) {
    gameState.bounty->verticalSpeed -= bountyAcceleration;
    if (gameState.bounty->verticalSpeed < 0) {
      gameState.bounty->verticalSpeed = 0;
    }
    gameState.bounty->bounds.y += gameState.bounty->verticalSpeed;
  } else if (IsKeyUp(KEY_UP) && !IsKeyDown(KEY_DOWN) && gameState.bounty->verticalSpeed < 0) {
    gameState.bounty->verticalSpeed += bountyAcceleration;
    if (gameState.bounty->verticalSpeed > 0) {
      gameState.bounty->verticalSpeed = 0;
    }
    gameState.bounty->bounds.y += gameState.bounty->verticalSpeed;
  }

  if (gameState.bounty->verticalSpeed != 0) {
    gameState.bounty->rotation = gameState.bounty->horizontalDirection * Remap(gameState.bounty->verticalSpeed, -bountyMaxSpeed, bountyMaxSpeed, -bountyMaxRotation, bountyMaxRotation);
  } else {
    gameState.bounty->rotation = 0;
  }

  if (gameState.bounty->rotation > bountyMaxRotation) {
    gameState.bounty->rotation = bountyMaxRotation;
  } else if (gameState.bounty->rotation < -bountyMaxRotation) {
    gameState.bounty->rotation = -bountyMaxRotation;
  }

  if (gameState.bounty->bounds.x < gameState.bounty->bounds.width / 2)
    gameState.bounty->bounds.x = gameState.bounty->bounds.width / 2;
  if (gameState.bounty->bounds.x > GetScreenWidth() - gameState.bounty->bounds.width / 2)
    gameState.bounty->bounds.x = GetScreenWidth() - gameState.bounty->bounds.width / 2;
  if (gameState.bounty->bounds.y < headerHeight + gameState.bounty->bounds.height / 2)
    gameState.bounty->bounds.y = headerHeight + gameState.bounty->bounds.height / 2;
  if (gameState.bounty->bounds.y > GetScreenHeight() - gameState.bounty->bounds.height / 2)
    gameState.bounty->bounds.y = GetScreenHeight() - gameState.bounty->bounds.height / 2;

  // Konami codes
  if (IsKeyPressed(KEY_SPACE)) {
    gameState.currentWordIndex++;
    initializeCurrentWord();
  }
}

static void interactions() {
  const char *currentWord = getCurrentWord();
  int currentWordLength = strlen(currentWord);
  ListNode *iterator = gameState.lettersPositions;
  int i = 0;
  bool catched = false;
  Rectangle bountyHitbox = {gameState.bounty->bounds.x - gameState.bounty->bounds.width / 2, gameState.bounty->bounds.y - gameState.bounty->bounds.height / 2, gameState.bounty->bounds.width, gameState.bounty->bounds.height};
  while (!catched && iterator != NULL) {
    LetterPosition *letterPosition = (LetterPosition *)iterator->val;
    if (letterPosition->letter == currentWord[gameState.currentLetterIndex] &&
        CheckCollisionRecs(bountyHitbox, letterPosition->position) &&
        !letterPosition->catched) {
      gameState.lettersPositions = removeElementAt(gameState.lettersPositions, i);
      gameState.currentLetterIndex = (gameState.currentLetterIndex + 1) % currentWordLength;
      catched = true;
      letterPosition->catched = true;
    }
    i++;
    iterator = iterator->next;
  }
  if (catched && gameState.currentLetterIndex == 0) {
    gameState.currentWordIndex++;
    initializeCurrentWord();
  }
}

static void printLettersPositions() {
  ListNode *iterator = gameState.lettersPositions;
  while (iterator != NULL) {
    printf("%c", ((LetterPosition *)iterator->val)->letter);
    iterator = iterator->next;
  }
  printf("\n");
}

const char *getCurrentWord() {
  return words[gameState.wordIndexes[gameState.currentWordIndex]];
}

static void drawBackground() {
  DrawTexture(backgroundTexture, 0, 0, WHITE);
}

static Vector2 getInitialPoint() {
  return (Vector2){GetScreenWidth() / 2, (GetScreenHeight() - headerHeight) / 2};
}