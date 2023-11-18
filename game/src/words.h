#ifndef LETTER_CATCHER_WORDS
#define LETTER_CATCHER_WORDS

#include "gameState.h"

static const int NUMBER_OF_WORDS = 14;
static char *words[] = {
    "NINJAGO",
    "LLOYD",
    "KAI",
    "BICICLETA",
    "LEGO",
    "MALAGA",
    "ABELLA",
    "OPITA",
    "ROSAPEREZ",
    "JOEL",
    "MAMI",
    "PELICULA",
    "ABUNOCHI",
    "TORTITAS"};

void initializeWords(GameState *gameState);

#endif