#include "test_map.h"
#include "test_mapobj.h"
#include "test_wolf.h"
#include "test_rabbit.h"
#include "test_cole.h"
#include "map.h"
#include "mapobj.h"
#include "wolf.h"
#include "rabbit.h"
#include "cole.h"

int main() {
    printf("=== COMPLETE ECOSYSTEM SIMULATION TESTS ===\n");

    // 1. Тесты базовых объектов
    printf("\n1. Basic object tests:\n");
    t_create_mapobj();
    t_mapobj_movement();
    t_mapobj_find_target();
    t_mapobj_eat();
    t_mapobj_give_s();
    t_mapobj_is_alive();
    t_mapobj_chase_target();

    // 2. Тесты конкретных классов
    printf("\n2. Specific class tests:\n");
    t_create_wolf();
    t_update_agg();
    t_create_rabbit();
    t_create_cole();

    // 3. Тесты карты
    printf("\n3. Map tests:\n");
    t_create_map();
    t_map_get_objects();
    t_map_kill_objects();
    t_map_make_step();
    t_map_game_over();

    // 4. Комплексные тесты на конкретной карте
    printf("\n4. Comprehensive tests on specific map:\n");

    Map* test_map = new Map(2, 3, 2); // 2 волка, 3 зайца, 2 капусты

    printf("\n--- Comprehensive MapObj tests ---\n");
    t_mapobj_comprehensive(test_map);

    printf("\n--- Comprehensive Map tests ---\n");
    t_map_comprehensive();

    printf("\n--- Wolf tests on map ---\n");
    t_wolf_on_map(test_map);

    printf("\n--- Rabbit tests on map ---\n");
    t_rabbit_on_map(test_map);

    printf("\n--- Cole tests on map ---\n");
    t_cole_on_map(test_map);

    printf("\n? ALL TESTS PASSED! Ecosystem simulation is working correctly.\n");

    delete test_map;
    return 0;
}