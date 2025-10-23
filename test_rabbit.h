#include "rabbit.h"
#include <cassert>

#ifndef TEST_RABBIT_H_
#define TEST_RABBIT_H_

bool t_create_rabbit(Rabbit* rabbit) {
    int x = rabbit->get_x();
    int y = rabbit->get_y();
    int s = rabbit->get_s();
    int rang = rabbit->get_rang();
    assert(x >= 0 && x <= MAX_COOR);
    assert(y >= 0 && y <= MAX_COOR);
    assert(s >= 0 && s <= MAX_STAMINA);
    assert(rang == 1); // Кролик всегда должен иметь ранг 1
    printf("Rabbit created correctly\n");
    return true;
}

bool t_rabbit_can_move(Rabbit* rabbit) {
    bool can_move = rabbit->can_be_moved();
    assert(can_move == true); // Кролик должен двигаться
    printf("Rabbit can move: %s\n", can_move ? "true" : "false");
    return true;
}

bool t_rabbit_alive(Rabbit* rabbit) {
    bool alive = rabbit->is_alive();
    assert(alive == (rabbit->get_s() > 0));
    printf("Rabbit is alive: %s\n", alive ? "true" : "false");
    return true;
}

#endif