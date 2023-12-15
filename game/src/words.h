#ifndef LETTER_CATCHER_WORDS
#define LETTER_CATCHER_WORDS

#include "gameState.h"

static const int NUMBER_OF_WORDS = 14;
static char *esWords[] = {
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
static char *deWords[] = {
    "NINJAGO",
    "LLOYD",
    "KAI",
    "FAHRRAD",
    "LEGO",
    "POKEMON",
    "SPIELEN",
    "BRUDER",
    "MAUS",
    "JOEL",
    "FREITAG",
    "SPIELPLATZ",
    "EISENBAHN",
    "HAND"};

void initializeWords(GameState *gameState);

#endif