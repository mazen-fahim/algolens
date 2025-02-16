#pragma once

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ANIMATION_SPEED 100

// 16:9
#define ALGO_WINDOW_WIDTH 960
#define ALGO_WINDOW_HEIGHT 540

#define CELL_WIDTH 20
#define CELL_HEIGHT 20

#define NUMBER_OF_ROWS (ALGO_WINDOW_HEIGHT / CELL_HEIGHT)
#define NUMBER_OF_COLS (ALGO_WINDOW_WIDTH / CELL_WIDTH)

#define BAR_WIDTH 20
#define NUMBER_OF_BARS (ALGO_WINDOW_WIDTH / BAR_WIDTH)
#define VALUE_RANGE ALGO_WINDOW_HEIGHT

// Frame rate of the application
#define FPS 144

// speed of the algorithm stepping
// how many updates per seond
#define UPS FPS
