#include "main.h"

// Constants
static const int screenWidth = 900;
static const int screenHeight = 900;

static const int headerHeight = 100;
static const int letterWidth = 50;
static const int letterHeight = 50;

static GameState gameState;

// Textures
Texture2D ribbonTexture;
Texture2D backgroundTexture;

Sprite2D *markerSprite;
Sprite2D *dragonSprite;

int main(void) {
  initiliaze();
  while (!WindowShouldClose()) {
    processInput();
    interactions();
    UpdateDrawFrame();
  }

  destroyBounty(gameState.bounty);
  destroyAsset(markerSprite);
  destroyAsset(dragonSprite);

  UnloadTexture(ribbonTexture);
  UnloadTexture(backgroundTexture);

  CloseWindow();

  return 0;
}

// TODO: Generalize movements and move it to a separate file
// TODO: Effects and sound when a letter is catched or the word/game is finished

void initiliaze() {
  gameState.currentWordIndex = 0;
  InitWindow(screenWidth, screenHeight, "Letter Catcher");
  SetTargetFPS(60);
  initializeFont();
  initializeWords(&gameState);
  initializeCurrentWord();
  gameState.bounty = createBounty(getInitialPoint());
  ribbonTexture = LoadTexture("resources/ribbons.png");
  backgroundTexture = LoadTexture("resources/clouds_background.png");
  dragonSprite = initializeDragon();
  markerSprite = initializeMarker();
}

void UpdateDrawFrame(void) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  // drawGrid();
  drawBackground();
  drawCurrentWord();
  drawLeftLetters();
  drawBounty(gameState.bounty);

  EndDrawing();
}

void initializeCurrentWord() {
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

void drawCurrentWord() {
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

void drawLeftLetters() {
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
      drawSprite(dragonSprite, dragonPosition);
    }
    iterator = iterator->next;
    i++;
  }
}

void processInput() {
  processInputForBounty(gameState.bounty);

  // Konami codes
  if (IsKeyPressed(KEY_SPACE)) {
    gameState.currentWordIndex++;
    initializeCurrentWord();
  }
}

void interactions() {
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

void printLettersPositions() {
  ListNode *iterator = gameState.lettersPositions;
  while (iterator != NULL) {
    printf("%c", ((LetterPosition *)iterator->val)->letter);
    iterator = iterator->next;
  }
  printf("\n");
}

char *getCurrentWord() {
  return words[gameState.wordIndexes[gameState.currentWordIndex]];
}

void drawBackground() {
  DrawTexture(backgroundTexture, 0, 0, WHITE);
}

Vector2 getInitialPoint() {
  return (Vector2){GetScreenWidth() / 2, (GetScreenHeight() - headerHeight) / 2};
}