#include <stdio.h>
#include <curses.h>
#include <stdbool.h>

// #define INIT_SNAKE_CAPACITY 16
#define INIT_SNAKE_CAPACITY 4

typedef struct
{
    int posX;
    int posY;
} node_s;

typedef struct
{
    bool alive;
    int posX;
    int posY;
    int dirX;
    int dirY;
    size_t size;
    size_t capacity;
    const char *icon;
    node_s **nodes;
} snake_s;

snake_s* spawn_snake(const char *icon, int posX, int posY);
void destroy_snake(snake_s *snake);
void move_snake(snake_s*, int pressed);
