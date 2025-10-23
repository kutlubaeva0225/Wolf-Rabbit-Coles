#include "mapobj.h"
#include <cassert>

#ifndef TEST_MAPOBJ_H_
#define TEST_MAPOBJ_H_

bool t_create_mapobj(MapObj* obj, int expected_rang) {
    int x = obj->get_x();
    int y = obj->get_y();
    int s = obj->get_s();
    int rang = obj->get_rang();
    assert(x >= 0 && x <= MAX_COOR);
    assert(y >= 0 && y <= MAX_COOR);
    assert(s >= 0 && s <= MAX_STAMINA);
    assert(rang == expected_rang);
    printf("MapObj created correctly (rang=%d)\n", rang);
    return true;
}

bool t_mapobj_give_s(MapObj* obj) {
    int old_stamina = obj->get_s();
    bool result = obj->give_s(1);
    int new_stamina = obj->get_s();
    assert(result == true || result == false); // Может вернуть false если превышен лимит
    if (result) {
        assert(new_stamina == old_stamina + 1);
    }
    printf("MapObj give_s: %s, stamina: %d -> %d\n",
        result ? "true" : "false", old_stamina, new_stamina);
    return true;
}

bool t_mapobj_alive(MapObj* obj) {
    bool alive = obj->is_alive();
    assert(alive == (obj->get_s() > 0));
    printf("MapObj is alive: %s (stamina=%d)\n", alive ? "true" : "false", obj->get_s());
    return true;
}

#endif
