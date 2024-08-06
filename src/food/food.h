#include <curses.h>
#include <stdio.h>

typedef struct
{
    int posX;
    int posY;
    const char *icon;
    size_t field_size;
} food_s;

food_s* spawn_food(const char *icon, size_t field_size);
void destroy_food(food_s *food);
void respawn_food(food_s *food);
