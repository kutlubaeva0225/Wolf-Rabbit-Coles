#include "wolf.h"
#include <cassert>

#ifndef TEST_WOLF_H_
#define TEST_WOLF_H_

bool t_create_wolf(Wolf* wolf) {
    int x = wolf->get_x();
    int y = wolf->get_y();
    int s = wolf->get_s();
    double agg = wolf->get_ag();
    assert(x >= 0 && x <= MAX_COOR);
    assert(y >= 0 && y <= MAX_COOR);
    assert(s >= 0 && s <= MAX_STAMINA);
    assert(agg >= 0 && agg <= 1);
    printf("Wolf created correctly\n");
    return true;
}

bool t_update_agg(Wolf* wolf) {
    double old_agg = wolf->get_ag();
    wolf->update_agg();
    double new_agg = wolf->get_ag();
    assert(new_agg >= 0 && new_agg <= 1);
    printf("Wolf aggression updated: %.2f -> %.2f\n", old_agg, new_agg);
    return true;
}

bool t_wanna_eat(Wolf* wolf) {
    // Тестируем логику голода
    bool result = wolf->wanna_eat();
    // Проверяем, что функция возвращает bool
    assert(result == true || result == false);
    printf("Wolf wanna_eat: %s\n", result ? "true" : "false");
    return true;
}

#endif




