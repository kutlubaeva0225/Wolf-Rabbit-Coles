#include "cole.h"
#include "map.h"
#include <cassert>

#ifndef TEST_COLE_H_
#define TEST_COLE_H_

// Тест создания капусты (без карты)
bool t_create_cole() {
    Cole* cole = new Cole(7, 7, 1, 0);
    assert(cole->get_x() == 7);
    assert(cole->get_y() == 7);
    assert(cole->get_s() == 1);  // У капусты всегда 1 stamina
    assert(cole->get_rang() == 0);
    assert(cole->can_be_moved() == false);  // Капуста не двигается
    printf("Cole created correctly\n");
    delete cole;
    return true;
}

// Тест поведения капусты на КОНКРЕТНОЙ карте
bool t_cole_on_map(Map* test_map) {
    printf("Testing cole behavior on specific map...\n");

    std::vector<MapObj*> objects = test_map->get_obj();
    int cole_count = 0;

    for (MapObj* obj : objects) {
        if (Cole* cole = dynamic_cast<Cole*>(obj)) {
            cole_count++;
            printf("Testing cole %d at position (%d, %d)\n",
                cole_count, cole->get_x(), cole->get_y());

            // Тестируем базовые свойства капусты
            assert(cole->get_rang() == 0);
            assert(cole->get_s() == 1);
            assert(cole->can_be_moved() == false);

            // Тестируем, что капуста не может есть
            bool eat_result = cole->eat(test_map);
            assert(eat_result == false);
            printf("Cole cannot eat: %s\n", eat_result ? "true" : "false");

            // Тестируем, что капуста не может двигаться
            bool move_result = cole->move_on(1, 1, test_map, false);
            assert(move_result == false);
            printf("Cole cannot move: %s\n", move_result ? "true" : "false");

            // Тестируем подкармливание капусты
            int old_stamina = cole->get_s();
            bool feed_result = cole->give_s(1);
            int new_stamina = cole->get_s();
            printf("Cole give_s result: %s, stamina: %d -> %d\n",
                feed_result ? "true" : "false", old_stamina, new_stamina);

            // Тестируем, что капуста всегда жива (stamina = 1)
            assert(cole->is_alive() == true);
            printf("Cole is always alive: %s\n", cole->is_alive() ? "true" : "false");

            // Тестируем поиск целей (капуста никого не ищет)
            MapObj* target = cole->find_targ(0, test_map);
            assert(target == nullptr);
            printf("Cole cannot find targets: %s\n", target ? "true" : "false");
        }
    }

    printf("Tested %d coles on map\n", cole_count);
    return true;
}

#endif