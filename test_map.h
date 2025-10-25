#include "map.h"
#include <cassert>

#ifndef TEST_MAP_H_
#define TEST_MAP_H_

// Тест создания карты
bool t_create_map() {
    Map* test_map = new Map(2, 3, 2); // 2 волка, 3 зайца, 2 капусты

    assert(test_map != nullptr);
    printf("Map created successfully\n");

    // Проверяем начальное состояние
    test_map->print();

    delete test_map;
    return true;
}

// Тест получения объектов с карты
bool t_map_get_objects() {
    Map* test_map = new Map(1, 2, 1); // 1 волк, 2 зайца, 1 капуста

    std::vector<MapObj*> objects = test_map->get_obj();

    // Проверяем, что получили правильное количество объектов
    assert(objects.size() == 4); // 1 + 2 + 1 = 4

    int wolf_count = 0, rabbit_count = 0, cole_count = 0;

    for (MapObj* obj : objects) {
        assert(obj != nullptr);
        assert(obj->get_x() >= 0 && obj->get_x() <= MAX_COOR);
        assert(obj->get_y() >= 0 && obj->get_y() <= MAX_COOR);

        if (obj->get_rang() == 2) wolf_count++;
        else if (obj->get_rang() == 1) rabbit_count++;
        else if (obj->get_rang() == 0) cole_count++;
    }

    printf("Objects on map: %d wolves, %d rabbits, %d coles\n",
        wolf_count, rabbit_count, cole_count);
    assert(wolf_count == 1);
    assert(rabbit_count == 2);
    assert(cole_count == 1);

    delete test_map;
    return true;
}

// Тест уничтожения объектов на карте
bool t_map_kill_objects() {
    Map* test_map = new Map(1, 1, 1); // 1 волк, 1 заяц, 1 капуста

    std::vector<MapObj*> objects = test_map->get_obj();
    assert(objects.size() == 3);

    // Находим зайца для уничтожения
    MapObj* rabbit_to_kill = nullptr;
    for (MapObj* obj : objects) {
        if (obj->get_rang() == 1) {
            rabbit_to_kill = obj;
            break;
        }
    }

    assert(rabbit_to_kill != nullptr);

    // Уничтожаем зайца
    test_map->kill(rabbit_to_kill);

    // Проверяем, что объект удален
    std::vector<MapObj*> objects_after_kill = test_map->get_obj();
    assert(objects_after_kill.size() == 2);

    printf("Object killed successfully. Remaining objects: %zu\n", objects_after_kill.size());

    delete test_map;
    return true;
}

// Тест шага моделирования
bool t_map_make_step() {
    Map* test_map = new Map(1, 1, 1);

    printf("Before step:\n");
    test_map->print();

    // Выполняем шаг
    test_map->make_step();

    printf("After step:\n");
    test_map->print();

    printf("Step completed successfully\n");

    delete test_map;
    return true;
}

// Тест проверки окончания игры
bool t_map_game_over() {
    // Тест 1: Не все объекты одного типа
    Map* test_map1 = new Map(1, 1, 1);
    bool game_over1 = test_map1->if_game_over();
    assert(game_over1 == false);
    printf("Game with multiple types: %s\n", game_over1 ? "OVER" : "CONTINUE");

    // Тест 2: Только волки
    Map* test_map2 = new Map(2, 0, 0);
    bool game_over2 = test_map2->if_game_over();
    printf("Game with only wolves: %s\n", game_over2 ? "OVER" : "CONTINUE");

    // Тест 3: Только зайцы  
    Map* test_map3 = new Map(0, 2, 0);
    bool game_over3 = test_map3->if_game_over();
    printf("Game with only rabbits: %s\n", game_over3 ? "OVER" : "CONTINUE");

    // Тест 4: Только капуста
    Map* test_map4 = new Map(0, 0, 2);
    bool game_over4 = test_map4->if_game_over();
    printf("Game with only coles: %s\n", game_over4 ? "OVER" : "CONTINUE");

    delete test_map1;
    delete test_map2;
    delete test_map3;
    delete test_map4;
    return true;
}

// Комплексный тест всей карты
bool t_map_comprehensive() {
    printf("=== COMPREHENSIVE MAP TESTS ===\n");

    // Создаем карту
    Map* test_map = new Map(2, 3, 2);

    // Тест 1: Проверяем начальное состояние
    printf("\n1. Initial state:\n");
    test_map->print();
    std::vector<MapObj*> initial_objects = test_map->get_obj();
    assert(initial_objects.size() == 7); // 2 + 3 + 2

    // Тест 2: Выполняем несколько шагов
    printf("\n2. Simulating 5 steps:\n");
    for (int i = 0; i < 5; i++) {
        printf("Step %d:\n", i + 1);
        test_map->make_step();
        test_map->print();

        // Проверяем, что игра не закончилась раньше времени
        //if (i < 4) {
          //  assert(test_map->if_game_over() == false);
        //}
    }

    // Тест 3: Уничтожаем несколько объектов
    printf("\n3. Testing object destruction:\n");
    std::vector<MapObj*> objects_before_kill = test_map->get_obj();
    if (objects_before_kill.size() > 2) {
        // Уничтожаем первый объект
        test_map->kill(objects_before_kill[0]);
        std::vector<MapObj*> objects_after_kill = test_map->get_obj();
        printf("Objects after kill: %zu -> %zu\n",
            objects_before_kill.size(), objects_after_kill.size());
    }

    // Тест 4: Проверяем конечное состояние
    printf("\n4. Final state:\n");
    test_map->print();
    bool final_game_state = test_map->if_game_over();
    printf("Game over: %s\n", final_game_state ? "YES" : "NO");

    delete test_map;
    printf("Comprehensive map tests completed\n");
    return true;
}

#endif