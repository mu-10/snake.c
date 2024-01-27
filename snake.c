#include "snake.h"
#include "paint.h"

#include <stdio.h>

void world_field(int world[Y_SIZE][X_SIZE], apple_t *apple,
                 snake_t *snake)
{
  // TODO
// Initialise the world image, which is a rectangle of grass
// surrounded by four walls. Place the snake and the apple
// in the world. 
  image_init(world, GRASS);
  add_rectangle(world, WALL, 0, 0, 80, 20);
  int col = apple->x;
  int row = apple->y;
  add_point(world, APPLE, col, row);
  add_points(world, SNAKE_BODY, snake->x, snake->y, snake->length);
  add_point(world,SNAKE_HEAD,snake->x[0],snake->y[0]);

}

void snake_init(snake_t *snake)
{
  // TODO
  // Initialise the snake in the game. The snake's head is positioned
  // at the centre of the world field, the snake has a length of 2,
  // and the snake should be travelling rightwards (so it's tail is
  // located to the left of the head).
  snake->length = 2;
  snake->x[0] = 40;
  snake->y[0] = 10;
  for (int x = 1; x <= snake->length; x++)
  {
    snake->x[x] = 40 - x;
    snake->y[x] = 10;
  }
  snake->dir = RIGHT;
}

void snake_turn(snake_t *snake) {
  if (kbhit()) {          // user hits key
    int input = getch();  // fetch the key value to input
    // TODO
	switch (input)
    {
    case 'w':
      snake->dir = UP;
      break;
    case 's':
      snake->dir = DOWN;
      break;
    case 'a':
      snake->dir = LEFT;
      break;
    case 'd':
      snake->dir = RIGHT;
      break;
    default:
      // Do nothing
      break;
    }
  }
}

void snake_move(snake_t *snake)
{
  // TODO
  // HInt: start by updating snake positions from the last part of the tail to segment behind head
  //       then update the position of the head

  // Update the position of the snake. The function
  // should move the snake forward by one position.
  switch (snake->dir)
  {
  case UP:
    for (int x = snake->length - 1; x > 0; x--)
    {
      // SNAKE BODY
      snake->x[x] = snake->x[x - 1];
      snake->y[x] = snake->y[x - 1];
    }
    // SNAKE HEAD
    snake->x[0] = snake->x[0];
    snake->y[0] = snake->y[0] - 1;
    break;

  case RIGHT:
    for (int x = snake->length - 1; x > 0; x--)
    {
      // SNAKE BODY
      snake->x[x] = snake->x[x - 1];
      snake->y[x] = snake->y[x - 1];
    }
    // SNAKE HEAD
    snake->x[0] = snake->x[0] + 1;
    snake->y[0] = snake->y[0];
    break;

  case DOWN:
    for (int x = snake->length - 1; x > 0; x--)
    {
      // SNAKE BODY
      snake->x[x] = snake->x[x - 1];
      snake->y[x] = snake->y[x - 1];
    }
    // SNAKE HEAD
    snake->x[0] = snake->x[0];
    snake->y[0] = snake->y[0] + 1;
    break;

  case LEFT:
    for (int x = snake->length - 1; x > 0; x--)
    {
      // SNAKE BODY
      snake->x[x] = snake->x[x - 1];
      snake->y[x] = snake->y[x - 1];
    }
    // SNAKE HEAD
    snake->x[0] = snake->x[0] - 1;
    snake->y[0] = snake->y[0];
    break;

  default:
    break;
  }
}

bool snake_hit_wall(snake_t *snake)
{
  // TODO
  // Check if the head of the snake hits a wall, and return true if so.
  if (snake->y[0] == 0 || snake->y[0] == 19 || snake->x[0] == 0 || snake->x[0] == 79)
  {
    return true;
  }
  return false;
}

bool snake_hit_self(snake_t *snake)
{
  // TODO
  // Check if the head of the snake hits another segment of its body.
  // Return true if so.
  for (int x = 1; x < snake->length; x++)
    if (snake->x[0] == snake->x[x] && snake->y[0] == snake->y[x])
    {
      return true;
    }
  return false;
}

void apple_new(apple_t *apple, snake_t *snake)
{
  // TODO
  // Hint: Draw random positions for the apple until position not hitting snake found

  // Place an apple in a random position in the world, making sure that
  // the apple is not placed in a position already occupied by the
  // snake.
  bool bad_position = true;
  while (bad_position)
  {
    //srand((unsigned)time(NULL));
    int col = rand() % 38 + 1;
    int row = rand() % 18 + 1;
    apple->x = col;
    apple->y = row;
    for (int x = 1; x < snake->length; x++)
      if (apple->x == snake->x[x] && apple->y == snake->y[x])
      {
        bad_position = true;
      }
      else
      {
        bad_position = false;
      }
  }
}

bool snake_eat_apple(apple_t *apple, snake_t *snake)
{
  // TODO
  // Check if the snake has eaten an apple (i.e. the snake's head is
  // at the same position as the apple). If so, increase the snake's
  // length, generate a new apple, and return true.
  if (snake->x[0] == apple->x && snake->y[0] == apple->y)
  {
    snake->length++;
    apple_new(apple, snake);
    return true;
  }
  return false;
}