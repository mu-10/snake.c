#include "hardware.h"
#include "paint.h"
#include "paint.c"      // Include the 'paint' library
#include "snake.h"      // Include the 'snake' library
#include "snake.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define EQUALS(v1, v2) printf( (v1) == (v2) ? "Ok\n" : "Not ok\n")

// Set paint's size parameters to be equal to the snake ones
const int NCOLS = X_SIZE; 
const int NROWS = Y_SIZE;

// ----- The test methods ----------------------------
void test_snake_init();
void test_insertSnakeBodyUnit();
void test_snake_move();
void test_snake_turn();
void test_snake_hit_self();
void test_snake_eat_apple();
void test_world_field();
void test_world_field();
//------ Help functions -------------------------------
void visualize_snake_init();
void visualize_apple_new();

int main() {
    
    srand(time(0));
    
    // TODO Uncomment test functions one at the time and test
    
    // -- uncomment what you want to test --
    
    test_world_field();
    test_snake_init();
    test_snake_move();
    test_snake_turn();
    test_snake_hit_self(); // to pass, this needs snake_turn to be working too
    test_snake_eat_apple();// to pass, this needs apple_new to be working too
    
    // -- Visual help functions, uncomment to use
    visualize_snake_init();
	visualize_apple_new();

    return(0);
}

// ------------ Test functions definitions -----------------

void test_world_field(){
    
    // Create test snake
    snake_t snake;
    snake.length = 2;
    snake.x[0] = 12;
    snake.x[1] = 12;
    snake.y[0] = 5;
    snake.y[1] = 4;
    
    // Create test apple
    apple_t apple;
    apple.x = 15;
    apple.y = 12;
    
    // Create world
    int world[NROWS][NCOLS];
    // insert snake and apple into the world
    world_field(world, &apple, &snake);
    // Print world with snake and apple
    image_print(world);
}

void visualize_snake_init(){
    
    // Create snake
    snake_t snake;
    // initialize snake
    snake_init(&snake);
    
    // Create test apple
    apple_t apple;
    apple.x = 15;
    apple.y = 12;
    // Create world
    int world[NROWS][NCOLS];
    // insert snake and apple into the world
    world_field(world, &apple, &snake);
    // Print world with snake and apple
    image_print(world);
}

void visualize_apple_new(){
    
    // Create test snake
    snake_t snake;
    int x[] = {41, 40, 39, 38, 37, 37, 37, 36, 35};
    int y[] = {10, 10, 10, 10, 10, 11, 12, 12, 12};
    int l = sizeof(x) / sizeof(x[0]);
    snake.length = l;
    for(int i = 0; i < snake.length; i++){
        snake.x[i] = x[i];
        snake.y[i] = y[i];
    }
    
    // Create apple
    apple_t apple;
    // initialize random apple
    apple_new(&apple, &snake);
    
    // Create world
    int world[NROWS][NCOLS];
    // insert snake and apple into the world
    world_field(world, &apple, &snake);
    // Print world with snake and apple
    image_print(world);
}

void test_snake_init(){
    printf("Test_snake_init\n");
    snake_t snake;
    snake_init(&snake);
    EQUALS(snake.dir, RIGHT);
    EQUALS(snake.x[0]*1000000+snake.y[0]*10000+snake.y[1]*100+snake.x[1], 40101039);
    EQUALS(snake.length, 2);
}

void test_snake_move(){
    printf("Test_snake_move\n");
    snake_t snake;

    snake_init(&snake);
    snake.length++;
    snake.dir = UP;
    snake_move(&snake);
    if (snake.x[0] != 40 || snake.x[1] != 40 || snake.x[2] != 39 || snake.y[0] != 9 || snake.y[1] != 10 || snake.y[2] != 10){
        printf("140 Not ok\n");
    } else {
        printf("142 Ok\n");
    }

    snake_init(&snake);
    snake.length++;
    snake.dir = DOWN;
    snake_move(&snake);
    if (snake.x[0] != 40 || snake.x[1] != 40 || snake.x[2] != 39 || snake.y[0] != 11 || snake.y[1] != 10 || snake.y[2] != 10){
        printf("150 Not ok\n");
    } else {
        printf("152 Ok\n");
    }

    snake_init(&snake);
    snake.dir = LEFT;
    snake_move(&snake);
    if (snake.x[0] != 39 || snake.x[1] != 40 || snake.y[0] != 10 || snake.y[1] != 10){
        printf("159 Not ok\n");
    } else {
        printf("161 Ok\n");
    }

    snake_init(&snake);
    snake.length++;
    snake.dir = RIGHT;
    snake_move(&snake);
    if (snake.x[0] != 41 || snake.x[1] != 40 || snake.x[2] != 39 || snake.y[0] != 10 || snake.y[1] != 10 || snake.y[2] != 10){
        printf("169 Not ok\n");
    } else {
        printf("171 Ok\n");
    }
}

void test_snake_eat_apple(){
    snake_t snake;
    snake_init(&snake);
    printf("Test_check_eat_apple\n");

    apple_t *apple = malloc(sizeof(apple_t));
    if (apple == NULL) {
        perror("Couldn't create apple, giving up");
        exit(EXIT_FAILURE);
    }

    apple->x = 14;
    apple->y = 12;
    EQUALS(snake_eat_apple(apple, &snake), 0);

    apple->x = 40;
    apple->y = 10;
    int osl = snake.length;
    int oxa = apple->x;
    int oya = apple->y;
    EQUALS(snake_eat_apple(apple, &snake), 1);   
    EQUALS(snake.length-osl, 1);
    if (oxa == apple->x && oya == apple->y){
        printf("Not ok\n");  // unlikely (but no impossible) that the new random apple takes the same spot.
    } else {
        printf("Ok\n");
    }
}


// These last two test functions have slight differences for Win and linux-macOS
#ifdef _WIN32
void test_snake_turn(){  // Windows function
    
    struct timespec ts;
    ts.tv_sec = 5;
    ts.tv_nsec = 125;
    
    printf("Test_snake_turn\n");
      
    snake_t snake;
    snake_init(&snake);
    
    printf("Just type the requested letter (within 5 seconds) and wait a few seconds, DO NOT type ENTER or any other key\n");

    printf("do left turn (%c): ", LEFT_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, LEFT);

    printf("do right turn (%c): ", RIGHT_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, RIGHT);

    printf("do up turn (%c): ", UP_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, UP);

    printf("do down turn (%c): ", DOWN_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, DOWN);

}

void test_snake_hit_self() {  // Windows function
    
    struct timespec ts;
    ts.tv_sec = 5;
    ts.tv_nsec = 125;
    
    printf("Test_snake_hit_self\n");
    snake_t snake;
    snake_init(&snake);

    printf("Just type the requested letter and wait a few seconds, DO NOT type ENTER or any other key\n");

    // Snake length is two and moving to the RIGHT (default at init)
    // Now turn the snake to the LEFT
    printf("type key %c: ", LEFT_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), false);

    // same in the up/down
    snake.dir = UP;
    printf("type key %c: ", DOWN_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);          // If length 2 never will collide!
    EQUALS(snake_hit_self(&snake), false);

    // If length > 2 possibly will collide!
    snake.dir = DOWN;
    snake.length = 3;
    printf("type key %c: ", UP_ARROW);
    nanosleep(&ts, NULL);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), true);
}

#else
void test_snake_turn(){  // Unix function
    printf("Test_snake_turn\n");
    int key;
    snake_t snake;
    snake_init(&snake);

    printf("do left turn (%c): ", LEFT_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, LEFT);

    printf("do right turn (%c): ", RIGHT_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, RIGHT);

    printf("do up turn (%c): ", UP_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, UP);

    printf("do down turn (%c): ", DOWN_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, DOWN);

}

void test_snake_hit_self() {  // Unix function
    printf("Test_snake_hit_self\n");
    int key;
    snake_t snake;
    snake_init(&snake);

    // Snake length is two and moving to the RIGHT (default at init)
    // Now turn the snake to the LEFT
    printf("type key %c: ", LEFT_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), false);

    // same in the up/down
    snake.dir = UP;
    printf("type key %c: ", DOWN_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);          // If length 2 never will collide!
    EQUALS(snake_hit_self(&snake), false);

    // If length > 2 possibly will collide!
    snake.dir = DOWN;
    snake.length = 3;
    printf("type key %c: ", UP_ARROW);
    scanf("%d", &key);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), true);
}

//End linux-macOS functions
#endif