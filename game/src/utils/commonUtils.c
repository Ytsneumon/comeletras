#include "commonUtils.h"

void initializeNumberArrayWithItsIndex(int *array, int start, int end) {
  int length = end - start;
  for (int i = 0; i < (length); i++) {
    array[i] = i + start;
  }
}

void initializeNumberArrayWithValue(int *array, int length, int value) {
  for (int i = 0; i < length; i++) {
    array[i] = value;
  }
}

bool contains(int *array, int value, int arraySize) {
  bool found = false;
  int i = 0;
  while (!found && i < arraySize) {
    found = array[i] == value;
    i++;
  }
  return found;
}