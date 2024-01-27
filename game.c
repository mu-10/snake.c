#include "hardware.h"
#include "paint.h"
#include "paint.c"	// Include the library of paint functions
#include "snake.h"	// Include the library of snake functions
#include "snake.c"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Set paint's size parameters to be equal to the snake ones
const int NCOLS = X_SIZE; 
const int NROWS = Y_SIZE; 

// Variables for game speed
#define START_WAIT 0.5 // s
#define SPEEDUP_FACTOR 0.9

// Snake's main
int main() {
  // Initalizations
  struct timespec ts;
  ts.tv_sec = (long)START_WAIT;
  ts.tv_nsec = (long)(START_WAIT * 1000000000) % 1000000000;
  
  srand(time(0));

  // Clear the screen, disabling the cursor if platform is Windows
  clrscr();

  // Create initial snake
  bool snake_dead = false;
  snake_t snake;
  snake_init(&snake);

  // Create initial apple
  apple_t apple;
  apple_new(&apple, &snake);

  // Create world
  int world[NROWS][NCOLS];
  world_field(world, &apple, &snake);

  // Loop until snake dies
  while (!snake_dead) {
    // Move to next snake state and put into world variable
    snake_turn(&snake);
    snake_move(&snake);
    world_field(world, &apple, &snake);
    
    // Print the world
    gotoxy(0, 0);
    image_print(world);
    printf("Points: %d\n", snake.length - 2);

    // Check eating or dying
    if (snake_eat_apple(&apple, &snake)) {
      ts.tv_nsec =
          ((long)(((ts.tv_sec * 1000000000) + ts.tv_nsec) * SPEEDUP_FACTOR)) %
          1000000000;
      ts.tv_sec = (long)ts.tv_sec * SPEEDUP_FACTOR;
    }
    snake_dead = snake_hit_wall(&snake) || snake_hit_self(&snake);
    if (snake_dead) {
      printf("Game over!!!\n");
    }
    
    // Wait a while
    nanosleep(&ts, NULL);
  }

  return (0);
}
