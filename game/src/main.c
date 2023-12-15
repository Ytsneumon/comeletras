#include "main.h"

// Constants
static const int screenWidth = 900;
static const int screenHeight = 900;

static const int headerHeight = 100;
static const int letterWidth = 50;
static const int letterHeight = 50;

static GameState gameState;

Texture2D backgroundTexture;
Texture2D ribbonTexture;
Texture2D esFlag;
Texture2D deFlag;
Sprite2D *markerSprite;

Sound explosion;
Sound wordCompleted;
Sound backgroundMusic;
Sound sword;

int main(void) {
  initiliaze();
  while (!WindowShouldClose()) {
    if (!IsSoundPlaying(backgroundMusic)) {
      PlaySound(backgroundMusic);
    }
    processInput();
    interactions();
    UpdateDrawFrame();
  }

  destroyBounty(gameState.bounty);
  destroyAsset(markerSprite);
  for (int i = 0; i < N_DRAGONS; i++) {
    destroyAsset(dragonSprites[i]);
  }

  UnloadTexture(ribbonTexture);
  UnloadTexture(backgroundTexture);
  UnloadSound(explosion);
  UnloadSound(wordCompleted);
  UnloadSound(backgroundMusic);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

void initiliaze() {
  gameState.scene = MAIN_MENU;
  gameState.currentWordIndex = 0;
  gameState.lettersPositions = NULL;
  gameState.language = ES;
  InitWindow(screenWidth, screenHeight, "Letter Catcher");
  InitAudioDevice();
  explosion = LoadSound("resources/explosion.wav");
  wordCompleted = LoadSound("resources/success.mp3");
  backgroundMusic = LoadSound("resources/ninjago_background_music.mp3");
  sword = LoadSound("resources/sword.mp3");
  SetSoundVolume(backgroundMusic, 0.5f);
  SetTargetFPS(60);
  gameState.bounty = createBounty(getInitialPoint());
  ribbonTexture = LoadTexture("resources/ribbons.png");
  backgroundTexture = LoadTexture("resources/clouds_background.png");
  esFlag = LoadTexture("resources/es_flag.png");
  deFlag = LoadTexture("resources/de_flag.png");
  markerSprite = initializeMarker();
  for (int i = 0; i < N_DRAGONS; i++) {
    dragonSprites[i] = initializeDragon(i);
  }
  initializeFont();
  initializeWords(&gameState);
  initializeCutScene();
}

void UpdateDrawFrame(void) {
  switch (gameState.scene) {
  case GAME:
    drawGameScene(gameState);
    break;
  case MAIN_MENU:
    drawMainMenu(gameState);
    break;
  case CUT_SCENE:
    drawCutScene();
    break;
  }
}

void initializeCurrentWord() {
  gameState.currentLetterIndex = 0;
  char *currentWord = getCurrentWord();
  int currentWordLength = strlen(currentWord);
  Vector2 *positions = malloc(currentWordLength * sizeof(Vector2));
  Rectangle mapBoundaries = {0, headerHeight, GetScreenWidth(), GetScreenHeight() - headerHeight};
  positionRandomly2D(positions, currentWordLength, letterWidth, letterHeight, mapBoundaries, 11, 5);
  initializeLettersPositions(&gameState, positions, currentWord, currentWordLength);
  free(positions);
}

void initializeLettersPositions(GameState *gameState, Vector2 *positions, char *letters, int length) {
  ListNode *iterator = gameState->lettersPositions;
  clearList(&gameState->lettersPositions);
  for (int i = 0; i < length; i++) {
    LetterPosition *letterPosition = malloc(sizeof(LetterPosition));
    letterPosition->position = (Rectangle){positions[i].x, positions[i].y, 50, 50};
    letterPosition->catched = false;
    letterPosition->letter = letters[i];
    letterPosition->dragonSprite = dragonSprites[rand() % N_DRAGONS];
    gameState->lettersPositions = addElement(gameState->lettersPositions, letterPosition);
  }
}

void processInput() {
  switch (gameState.scene) {
  case MAIN_MENU:
    processInputForMainMenu();
    break;
  case GAME:
    processInputForBounty(gameState.bounty);
    // Konami codes
    if (IsKeyPressed(KEY_SPACE)) {
      nextWord();
    }
    break;
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
      PlaySound(explosion);
      gameState.lettersPositions = removeElementAt(gameState.lettersPositions, i);
      gameState.currentLetterIndex = (gameState.currentLetterIndex + 1) % currentWordLength;
      catched = true;
      letterPosition->catched = true;
    }
    i++;
    iterator = iterator->next;
  }
  if (catched && gameState.currentLetterIndex == 0) {
    PlaySound(wordCompleted);
    nextWord();
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
  if (gameState.language == ES) {
    return esWords[gameState.wordIndexes[gameState.currentWordIndex]];
  } else {
    return deWords[gameState.wordIndexes[gameState.currentWordIndex]];
  }
}

Vector2 getInitialPoint() {
  return (Vector2){GetScreenWidth() / 2, (GetScreenHeight() - headerHeight) / 2};
}

void nextWord() {
  if (gameState.currentWordIndex < NUMBER_OF_WORDS - 1) {
    gameState.currentWordIndex++;
    initializeCurrentWord();
  } else {
    gameState.scene = CUT_SCENE;
  }
}

void processInputForMainMenu() {
  if (IsKeyDown(KEY_DOWN) && gameState.language == ES) {
    PlaySound(sword);
    gameState.language = DE;
  }
  if (IsKeyDown(KEY_UP) && gameState.language == DE) {
    PlaySound(sword);
    gameState.language = ES;
  }
  if (IsKeyDown(KEY_ENTER)) {
    gameState.scene = GAME;
    PlaySound(explosion);
    initializeCurrentWord();
    Vector2 bountyInitialPosition = getInitialPoint();
    gameState.bounty->bounds.x = bountyInitialPosition.x;
    gameState.bounty->bounds.y = bountyInitialPosition.y;
  }
}