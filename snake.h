#include <stdbool.h>
#include <stdlib.h>
#ifndef __SNAKE_H__
#define __SNAKE_H__

// For snake we define the size by these macros
// Here the two dimensions are called x and y
#define X_SIZE 80  // Horizontal size, including walls
#define Y_SIZE 20  // Vertical size, including walls

// macros to define keys for controlling the snake  
#define UP_ARROW 'w'
#define LEFT_ARROW 'a'
#define DOWN_ARROW 's'
#define RIGHT_ARROW 'd'

// Use externally defined function
extern int getch();
extern int kbhit();

// ----- Struct and enum definitions -----------------

// structure to represent an apple
typedef struct {
    int x, y;
} apple_t;

// enum to keep track of snake direction
typedef enum {
    UP, RIGHT, DOWN, LEFT
} dir_t;

// structure to represent a snake
typedef struct {
    int x[(X_SIZE-2)*(Y_SIZE-2)];
    int y[(X_SIZE-2)*(Y_SIZE-2)];
    int length;
    dir_t dir;
} snake_t;


// 
// The functions
//

// ----- The function for filling the world variable -----------------

// Initialise the world image, which is a rectangle of grass
// surrounded by four walls. Place the snake and the apple
// in the world. 
void world_field(int world[Y_SIZE][X_SIZE], apple_t *apple, snake_t *snake);

// ----- Functions for snake and apple -----------------

// Initialise the snake in the game. The snake's head is positioned
// at the centre of the world field, the snake has a length of 2,
// and the snake should be travelling rightwards (so it's tail is
// located to the left of the head).
void snake_init(snake_t *snake);

// Take input from the player (e.g. UP_ARROW, RIGHT_ARROW, etc)
// and change the direction that the snake is travelling,
// based on the input.
void snake_turn(snake_t *snake);

// Update the position of the snake. The function
// should move the snake forward by one position.
void snake_move(snake_t *snake);

// Check if the head of the snake hits a wall, and return true if so.
bool snake_hit_wall(snake_t *snake);

// Check if the head of the snake hits another segment of its body.
// Return true if so.
bool snake_hit_self(snake_t *snake);

// Place an apple in a random position in the world, making sure that
// the apple is not placed in a position already occupied by the
// snake.
void apple_new(apple_t *apple, snake_t *snake);

// Check if the snake has eaten an apple (i.e. the snake's head is
// at the same position as the apple). If so, increase the snake's
// length, generate a new apple, and return true.
bool snake_eat_apple(apple_t *apple, snake_t *snake);

#endif
