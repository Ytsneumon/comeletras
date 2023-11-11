#include "font.h"
#include "utils/commonUtils.h"
#include <stdio.h>
#include <string.h>

Font font = {0};

static const int charsetStartIndex = 0;
static const int charsetEndIndex = 255;

void initializeFont() {
  int codepoints[256];
  initializeNumberArrayWithItsIndex(codepoints, charsetStartIndex, charsetEndIndex);
  font = LoadFontEx(fileName, 50, codepoints, charsetEndIndex - charsetStartIndex);
  /* printf("Font info:\n");
  printf("Glyph count: %d\n", font.glyphCount);
  printf("Glyph padding: %d\n", font.glyphPadding);
  for (int i = 0; i < font.glyphCount; i++)
  {
    GlyphInfo glyphInfo = font.glyphs[i];
    printf(" Glyph %c:\n", glyphInfo.value);
    printf("  value: %d\n", glyphInfo.value);
    printf("  advanceX: %d\n", glyphInfo.advanceX);
  } */
}
