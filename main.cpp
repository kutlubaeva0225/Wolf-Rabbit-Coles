#include "test_wolf.h"
#include "test_rabbit.h"
#include "test_cole.h"
#include "test_mapobj.h"
#include "test_map.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    printf("=== Starting Tests ===\n");

    // Тесты Wolf
    printf("\n--- Testing Wolf ---\n");
    Wolf* wolf = new Wolf(5, 5, START_S, 2, 0.5);
    t_create_wolf(wolf);
    t_update_agg(wolf);
    t_wanna_eat(wolf);

    // Тесты Rabbit
    printf("\n--- Testing Rabbit ---\n");
    Rabbit* rabbit = new Rabbit(3, 3, START_S, 1);
    t_create_rabbit(rabbit);
    t_rabbit_can_move(rabbit);
    t_rabbit_alive(rabbit);

    // Тесты Cole
    printf("\n--- Testing Cole ---\n");
    Cole* cole = new Cole(7, 7, 1, 0);
    t_create_cole(cole);
    t_cole_cannot_move(cole);
    t_cole_give_s(cole);

    // Тесты MapObj
    printf("\n--- Testing MapObj ---\n");
    t_create_mapobj(wolf, 2);
    t_mapobj_give_s(wolf);
    t_mapobj_alive(wolf);

    // Тесты Map
    printf("\n--- Testing Map ---\n");
    Map* map = new Map(2, 3, 4); // 2 волка, 3 кролика, 4 капусты
    t_create_map(map);
    t_map_get_obj(map);
    t_map_kill(map);

    // Очистка
    delete wolf;
    delete rabbit;
    delete cole;
    delete map;

    printf("\n=== All Tests Passed! ===\n");
    return 0;
}