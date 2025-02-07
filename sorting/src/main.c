#include "../include/Draw.h"
#include "../include/GameLoop.h"
#include "../include/GameObjects.h"
#include "../include/Init.h"
#include "../include/globals.h"
#include <SDL2/SDL.h>
#define MAXLENGTH 100
#define VALUERANGE 100

int arrayOriginal[MAXLENGTH];
int arrayToSort[MAXLENGTH];
Rectangle *allRects[MAXLENGTH];
bool initialized = false;
// These variables are used to control the speed of the animation
int lastTick;
int currentTick;
int diff;

void visualize(void);
void setRectColor(Rectangle *, const char *);
int main(int argc, const char *argv[]) {
  /***** Initialization (window and renderer) ******/
  SDL_Window *window;
  SDL_Renderer *renderer;
  const unsigned windowWidth = 680;
  const unsigned windowHeight = 420;
  const char *title = "AlgoVisiualizer";
  Uint32 windowFlags = SDL_WINDOW_SHOWN;
  Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  if (!init(&window, title, windowWidth, windowHeight, windowFlags, &renderer,
            rendererFlags)) {
    exit(1);
  }

  // initialize the array with random numbers ranging from 0 to 100.
  for (int i = 0; i < MAXLENGTH; i++) {
    arrayOriginal[i] = rand() % (VALUERANGE + 1);
    arrayToSort[i] = arrayOriginal[i];
  }

  /***** Create game objects *****/
  const float rectWidth = windowWidth / (float)MAXLENGTH;
  int rectHeight; // this is int not float to solve pixel off by one bug.
  float rectX;
  float rectY;
  for (int i = 0; i < MAXLENGTH; i++) {
    rectHeight = arrayOriginal[i] / 100.0 * windowHeight;
    rectX = rectWidth * i;
    rectY = windowHeight - rectHeight;
    allRects[i] = createRectangle(i, rectX, rectY, rectWidth, rectHeight, 1, 0,
                                  0, 0, 0, 255, 255, 255, 255, false, NULL);
  }
  for (int i = 0; i < MAXLENGTH; i++) {
    printf("%d ", arrayOriginal[i]);
  }
  printf("\n");
  /***** Start the Game *****/
  visualize();
  return 0;
}

void visualize(void) {
  // selection sort
  int swaps = 0;
  int temp;
  for (int i = 0; i < MAXLENGTH - 1; i++) {
    // highlight what the index i is pointing at in green.
    setRectColor(allRects[i], "green");
    for (int k = i + 1; k < MAXLENGTH; k++) {
      // highlight what the index k is pointing at in red. and i in green.
      setRectColor(allRects[k], "red");
      if (arrayToSort[k] < arrayToSort[i]) {
        temp = arrayToSort[i];
        arrayToSort[i] = arrayToSort[k];
        arrayToSort[k] = temp;
        setRectColor(allRects[k], "blue");
        // update the state of the swapped rects
        allRects[i]->height =
            (int)arrayToSort[i] / 100.0 * windowGlobal.windowHeight;
        allRects[i]->y = windowGlobal.windowHeight - allRects[i]->height;
        allRects[k]->height =
            (int)arrayToSort[k] / 100.0 * windowGlobal.windowHeight;
        allRects[k]->y = windowGlobal.windowHeight - allRects[k]->height;
        swaps++;
      }
      // update the state of the rects
      draw();
      setRectColor(allRects[k], "white");
    }
  }
  printf("Number of swaps: %d\n", swaps);
}
void setRectColor(Rectangle *rect, const char *color) {
  if (!strcmp(color, "red")) {
    rect->red = 255;
    rect->blue = 0;
    rect->green = 0;
    rect->alpha = 255;
  } else if (!strcmp(color, "blue")) {
    rect->red = 0;
    rect->blue = 255;
    rect->green = 0;
    rect->alpha = 255;
  } else if (!strcmp(color, "green")) {
    rect->red = 0;
    rect->blue = 0;
    rect->green = 255;
    rect->alpha = 255;
  } else if (!strcmp(color, "white")) {
    rect->red = 255;
    rect->blue = 255;
    rect->green = 255;
    rect->alpha = 255;
  }
}
