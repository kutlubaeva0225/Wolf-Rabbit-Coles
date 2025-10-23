#include "map.h"
#include <cassert>

#ifndef TEST_MAP_H_
#define TEST_MAP_H_

bool t_create_map(Map* map) {
    int wolfs = 0, rabbits = 0, coles = 0;
    // Подсчитываем объекты по типам
    auto objects = map->get_obj();
    for (auto obj : objects) {
        if (dynamic_cast<Wolf*>(obj)) wolfs++;
        else if (dynamic_cast<Rabbit*>(obj)) rabbits++;
        else if (dynamic_cast<Cole*>(obj)) coles++;
    }

    assert(wolfs >= 0);
    assert(rabbits >= 0);
    assert(coles >= 0);
    assert(objects.size() == wolfs + rabbits + coles);

    printf("Map created: %d wolves, %d rabbits, %d coles, total: %zu objects\n",
        wolfs, rabbits, coles, objects.size());
    return true;
}

bool t_map_kill(Map* map) {
    auto objects_before = map->get_obj();
    size_t count_before = objects_before.size();

    if (count_before > 0) {
        MapObj* target = objects_before[0];
        map->kill(target);

        auto objects_after = map->get_obj();
        size_t count_after = objects_after.size();

        assert(count_after == count_before - 1);
        printf("Map kill test: %zu -> %zu objects\n", count_before, count_after);
    }
    return true;
}

bool t_map_get_obj(Map* map) {
    auto objects = map->get_obj();
    for (auto obj : objects) {
        assert(obj != nullptr);
        assert(obj->get_x() >= 0 && obj->get_x() <= MAX_COOR);
        assert(obj->get_y() >= 0 && obj->get_y() <= MAX_COOR);
    }
    printf("Map get_obj test: %zu objects are valid\n", objects.size());
    return true;
}

#endif
