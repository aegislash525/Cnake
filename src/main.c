#include <unistd.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "food/food.h"
#include "snake/snake.h"

#define FIELD_SIZE 30

#define FOOD_ICON "&"
#define SNAKE_ICON "o"
#define SNAKE_HEAD_ICON "x"

#define WALLS_X "-"
#define WALLS_Y "|"

#define SLEEP_TIME 100000
#define BUFF_SIZE 64

void draw_walls(size_t field_size, const char *x, const char *y);

int main(void)
{
    WINDOW *win = initscr();
    keypad(win, true);
    nodelay(win, true);

    food_s *food = spawn_food(FOOD_ICON, FIELD_SIZE);

    int initX = rand() % 20;
    int initY = rand() % 20;
    snake_s *snake = spawn_snake(SNAKE_ICON, initX, initY);

    node_s *node = (node_s *) malloc(sizeof(node_s));
    node->posX = snake->posX;
    node->posY = snake->posY;
    snake->nodes[0] = node;

    char message[BUFF_SIZE];
    unsigned short score = 1; // stack overflow in 65535 values
    bool dead = false;
    while (true) {
        if (dead)
        {
            snprintf(message, sizeof(message) - 1, "YOU LOSE! Your score: %u.", score);
            message[sizeof(message) - 1] = '\0';
            break;
        }
        char buff[BUFF_SIZE];
        snprintf(buff, sizeof(buff) - 1, "score: %u", score - 1);
        buff[sizeof(buff) - 1] = '\0';

        char info[BUFF_SIZE];
        snprintf(info, sizeof(info) - 1, "snake size: %zu", snake->size);
        info[sizeof(info) - 1] = '\0';

        move_snake(snake, wgetch(win));
        snake->size = score;

        // body position
        for (int i = snake->size - 1; i > 0; i--)
        {
            snake->nodes[i]->posX = snake->nodes[i - 1]->posX;
            snake->nodes[i]->posY = snake->nodes[i - 1]->posY;
        }
        snake->nodes[0]->posX = snake->posX;
        snake->nodes[0]->posY = snake->posY;
        snake->posX += snake->dirX;
        snake->posY += snake->dirY;

        erase();
        // game info positioning
        draw_walls(FIELD_SIZE + 1, WALLS_X, WALLS_Y);
        mvaddstr(FIELD_SIZE + 2, 0, info);
        mvaddstr(FIELD_SIZE + 2, FIELD_SIZE - strnlen(buff, sizeof(buff) - 1), buff);

        mvaddstr(food->posY, food->posX, food->icon);

        // draw body nodes
        for (size_t i = 0; i < snake->size; i++)
        {
            mvaddstr(snake->nodes[i]->posY,
                snake->nodes[i]->posX, snake->icon);

            // check if head hits body
            if (snake->posX == snake->nodes[i]->posX &&
                snake->posY == snake->nodes[i]->posY)
                dead = true;
        }

        // draw snake's head
        mvaddstr(snake->posY, snake->posX, SNAKE_HEAD_ICON);

        // eat food logic
        if (snake->posX == food->posX && snake->posY == food->posY)
        {
            respawn_food(food);
            if (score == (unsigned short) pow((double) FIELD_SIZE, (double) 2)) {
                // node array realloc
                snprintf(message, sizeof(message) - 1, "YOU WIN! Your score: %u.", score);
                message[sizeof(message) - 1] = '\0';
                break;
            }
            else if (score == snake->capacity)
            {
                node_s **tmp = realloc(snake->nodes, sizeof(node_s **) * (snake->capacity * 2));
                if (tmp == NULL)
                {
                    snprintf(message, sizeof(message) - 1,
                        "failed to reallocate snake's capacity.");
                    message[sizeof(message) - 1] = '\0';
                    break;
                }
                snake->capacity *= 2;
                snake->nodes = tmp;
            }
            // create and store node
            node_s *node = (node_s *) malloc(sizeof(node_s));
            node->posX = snake->posX;
            node->posY = snake->posY;
            snake->nodes[score] = node;
            score++;
        }
        usleep(SLEEP_TIME);

        if (snake->posX == FIELD_SIZE + 1 || snake->posX == 0)
            dead = true;
        else if (snake->posY == FIELD_SIZE + 1 || snake->posY == 0)
            dead = true;
    }
    endwin();
    destroy_snake(snake);
    destroy_food(food);

    puts(message);
    return EXIT_SUCCESS;
}

void draw_walls(size_t field_size, const char *x, const char *y)
{
    // top wall
    for (size_t i = 0; i < field_size; i++)
        mvaddstr(0, i, x);

    // bottom wall
    for (size_t i = 0; i < field_size; i++)
        mvaddstr(field_size, i, x);

    // left wall
    for (size_t i = 0; i < field_size; i++)
        mvaddstr(i, field_size, y);

    // right wall
    for (size_t i = 0; i < field_size; i++)
        mvaddstr(i, 0, y);
}
