#ifndef CELL_H
#define CELL_H
#include <SDL.h>

typedef struct Cell {
  float x;
  float y;
  float width;
  float height;
  float widthScale;
  float heightScale;
  int red;
  int green;
  int blue;
  int alpha;
  SDL_Rect rect;
} Cell;

#endif
