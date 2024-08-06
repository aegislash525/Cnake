#include <stdlib.h>
#include "snake.h"

snake_s* spawn_snake(const char *icon, int posX, int posY)
{
    snake_s *snake = (snake_s *) malloc(sizeof(snake_s));
    if (snake == NULL)
    {
        puts("failed to spawn snake.");
        endwin();
        exit(EXIT_FAILURE);
    }

    if (icon != NULL)
        snake->icon = icon;
    else
        snake->icon = "s";

    snake->size = 0;
    snake->capacity = INIT_SNAKE_CAPACITY;
    snake->nodes = (node_s **) malloc(sizeof(void *) * snake->capacity);

    if (snake->nodes == NULL)
    {
        puts("failed to spawn snake.");
        endwin();
        exit(EXIT_FAILURE);
    }

    snake->alive = true;
    snake->posX = posX;
    snake->posY = posY;
    snake->icon = icon;
    snake->dirX = 1;
    snake->dirY = 0;
    return snake;
}

void move_snake(snake_s* snake, int pressed)
{
    if (snake == NULL)
    {
        puts("failed to move the snake.");
        endwin();
        exit(EXIT_FAILURE);
    }
    switch (pressed) {
        case KEY_LEFT:
            if (snake->dirX != 1)
            {
                snake->dirX = -1;
                snake->dirY = 0;
                break;
            } else
                break;
        case KEY_RIGHT:
            if (snake->dirX != -1)
            {
                snake->dirX = 1;
                snake->dirY = 0;
                break;
            } else
                break;
        case KEY_UP:
            if (snake->dirY != 1)
            {
                snake->dirX = 0;
                snake->dirY = -1;
                break;
            } else
                break;
        case KEY_DOWN:
            if (snake->dirY != -1)
            {
                snake->dirX = 0;
                snake->dirY = 1;
                break;
            } else
                break;
        default:
            break;
    };
}

void destroy_snake(snake_s *snake)
{
    if (snake == NULL && snake->nodes != NULL)
    {
        puts("failed to destroy the snake.");
        endwin();
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < snake->size; i++)
    {
        if (snake->nodes[i] != NULL)
            free(snake->nodes[i]);
    }
    free(snake->nodes);
    free(snake);
}
