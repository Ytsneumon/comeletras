#ifndef UTILS_COMMON_UTILS
#define UTILS_COMMON_UTILS

#include <stdbool.h>

void initializeNumberArrayWithItsIndex(int *array, int start, int end);

void initializeNumberArrayWithValue(int *array, int length, int value);

bool contains(int *array, int value, int arraySize);

#endif