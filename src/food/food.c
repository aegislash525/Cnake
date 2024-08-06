#include <stdlib.h>
#include "food.h"

food_s* spawn_food(const char *icon, size_t field_size)
{
    food_s *food = (food_s *) malloc(sizeof(food_s));
    if (food == NULL)
    {
        puts("failed to spawn the food.");
        endwin();
        exit(EXIT_FAILURE);
    }

    if (icon != NULL)
        food->icon = icon;
    else
        food->icon = "f";

    food->field_size = field_size;
    food->posX = rand() % food->field_size;
    food->posY = rand() % food->field_size;
    return food;
}

void respawn_food(food_s *food)
{
    if (food == NULL)
    {
        puts("failed to respawn the food.");
        endwin();
        exit(EXIT_FAILURE);
    }
    food->posX = rand() % food->field_size;
    if (food->posX == 0)
        respawn_food(food);

    food->posY = rand() % food->field_size;
    if (food->posY == 0)
        respawn_food(food);
}

void destroy_food(food_s *food)
{
    if (food == NULL)
    {
        puts("failed to destroy the food.");
        endwin();
        exit(EXIT_FAILURE);
    }
    free(food);
}
