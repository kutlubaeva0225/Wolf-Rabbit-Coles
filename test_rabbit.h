#include "rabbit.h"
#include "map.h"
#include <cassert>

#ifndef TEST_RABBIT_H_
#define TEST_RABBIT_H_

// Тест создания зайца (без карты)
bool t_create_rabbit() {
    Rabbit* rabbit = new Rabbit(3, 3, START_S, 1);
    assert(rabbit->get_x() == 3);
    assert(rabbit->get_y() == 3);
    assert(rabbit->get_s() == START_S);
    assert(rabbit->get_rang() == 1);
    assert(rabbit->can_be_moved() == true);
    printf("Rabbit created correctly\n");
    delete rabbit;
    return true;
}

// Тест поведения зайца на КОНКРЕТНОЙ карте
bool t_rabbit_on_map(Map* test_map) {
    printf("Testing rabbit behavior on specific map...\n");

    std::vector<MapObj*> objects = test_map->get_obj();
    int rabbit_count = 0;

    for (MapObj* obj : objects) {
        if (Rabbit* rabbit = dynamic_cast<Rabbit*>(obj)) {
            rabbit_count++;
            printf("Testing rabbit %d at position (%d, %d)\n",
                rabbit_count, rabbit->get_x(), rabbit->get_y());

            // Тестируем базовые свойства
            assert(rabbit->get_rang() == 1);
            assert(rabbit->get_s() >= 0);
            assert(rabbit->can_be_moved() == true);

            // Тестируем движение зайца
            int old_x = rabbit->get_x();
            int old_y = rabbit->get_y();
            int old_stamina = rabbit->get_s();

            bool move_result = rabbit->move_on(1, 1, test_map, false);
            printf("Rabbit moved from (%d,%d) to (%d,%d), stamina: %d -> %d\n",
                old_x, old_y, rabbit->get_x(), rabbit->get_y(), old_stamina, rabbit->get_s());

            // Тестируем поиск капусты
            MapObj* target = rabbit->find_targ(0, test_map); // Поиск в зоне видимости
            if (target) {
                printf("Rabbit found target at (%d,%d) - rang %d\n",
                    target->get_x(), target->get_y(), target->get_rang());
            }

            // Тестируем поедание капусты
            bool eat_result = rabbit->eat(test_map);
            printf("Rabbit eat result: %s\n", eat_result ? "true" : "false");
        }
    }

    printf("Tested %d rabbits on map\n", rabbit_count);
    return true;
}

#endif