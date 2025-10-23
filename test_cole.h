#include "cole.h"
#include <cassert>

#ifndef TEST_COLE_H_
#define TEST_COLE_H_

bool t_create_cole(Cole* cole) {
    int x = cole->get_x();
    int y = cole->get_y();
    int s = cole->get_s();
    int rang = cole->get_rang();
    assert(x >= 0 && x <= MAX_COOR);
    assert(y >= 0 && y <= MAX_COOR);
    assert(rang == 0); // Капуста всегда должна иметь ранг 0
    printf("Cole created correctly\n");
    return true;
}

bool t_cole_cannot_move(Cole* cole) {
    bool can_move = cole->can_be_moved();
    assert(can_move == false); // Капуста не должна двигаться
    printf("Cole can move: %s\n", can_move ? "true" : "false");
    return true;
}

bool t_cole_give_s(Cole* cole) {
    int old_stamina = cole->get_s();
    bool result = cole->give_s(COLE_P_S);
    int new_stamina = cole->get_s();
    assert(result == true);
    assert(new_stamina == old_stamina + COLE_P_S);
    printf("Cole stamina: %d -> %d\n", old_stamina, new_stamina);
    return true;
}

#endif
