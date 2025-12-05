#include "map.h"
#include <cassert>



// Òåñò ñîçäàíèÿ êàðòû
bool t_create_map() {
    Map* test_map = new Map(1, 2, 1); // 2 âîëêà, 3 çàéöà, 2 êàïóñòû

    assert(test_map != nullptr);
    printf("Map created successfully\n");

    // Ïðîâåðÿåì íà÷àëüíîå ñîñòîÿíèå
    test_map->print();

    delete test_map;
    return true;
}

// Òåñò ïîëó÷åíèÿ îáúåêòîâ ñ êàðòû
bool t_map_get_objects() {
    Map* test_map = new Map(1, 2, 1); // 1 âîëê, 2 çàéöà, 1 êàïóñòà

    std::vector<MapObj*> objects = test_map->get_obj();

    // Ïðîâåðÿåì, ÷òî ïîëó÷èëè ïðàâèëüíîå êîëè÷åñòâî îáúåêòîâ
    assert(objects.size() == 4); // 1 + 2 + 1 = 4

    int wolf_count = 0, rabbit_count = 0, cole_count = 0;

    for (MapObj* obj : objects) {
        assert(obj != nullptr);
        assert(obj->get_x() >= 0 && obj->get_x() <= MAX_COOR);
        assert(obj->get_y() >= 0 && obj->get_y() <= MAX_COOR);

        if (obj->get_rang() == 2) wolf_count++;
        else if (obj->get_rang() == 1) rabbit_count++;
        else if (obj->get_rang() == 0) cole_count++;
        printf("obj stamina is %d\n", obj->get_s());
    }

    printf("Objects on map: %d wolves, %d rabbits, %d coles\n", wolf_count, rabbit_count, cole_count);

    assert(wolf_count == 1);
    assert(rabbit_count == 2);
    assert(cole_count == 1);

    delete test_map;
    return true;
}

// Òåñò óíè÷òîæåíèÿ îáúåêòîâ íà êàðòå
bool t_map_kill_objects() {
    Map* test_map = new Map(1, 1, 1); // 1 âîëê, 1 çàÿö, 1 êàïóñòà

    std::vector<MapObj*> objects = test_map->get_obj();
    assert(objects.size() == 3);

    // Íàõîäèì çàéöà äëÿ óíè÷òîæåíèÿ
    MapObj* rabbit_to_kill = nullptr;
    for (MapObj* obj : objects) {
        if (obj->get_rang() == 1) {
            rabbit_to_kill = obj;
            break;
        }
    }

    assert(rabbit_to_kill != nullptr);

    // Óíè÷òîæàåì çàéöà
    test_map->kill(rabbit_to_kill);

    // Ïðîâåðÿåì, ÷òî îáúåêò óäàëåí
    std::vector<MapObj*> objects_after_kill = test_map->get_obj();
    assert(objects_after_kill.size() == 2);

    printf("Object killed successfully. Remaining objects: %zu\n", objects_after_kill.size());
    test_map->print();
    delete test_map;
    return true;
}

// Òåñò øàãà ìîäåëèðîâàíèÿ
bool t_map_make_step() {
    Map* test_map = create_map(1, 5, 1);

    printf("Before step:\n");

    m_print(test_map);

    // Ïðîâåðÿåì îáúåêòû ïåðåä øàãîì
    std::vector<MapObj*> objects = test_map->get_obj();
    printf("Objects before step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }

    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    make_step(test_map);

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }


    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    test_map->make_step();

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }


    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    make_step(test_map);

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }
    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    test_map->make_step();

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }


    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    make_step(test_map);

    printf("After step:\n");
    m_print(test_map);
    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    test_map->make_step();

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }


    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    make_step(test_map);

    printf("After step:\n");
    m_print(test_map);
    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    test_map->make_step();

    printf("After step:\n");
    m_print(test_map);

    objects = test_map->get_obj();
    printf("Objects after step: %zu\n", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        printf("  Object %zu: type=%d, pos=(%d,%d), stam = %d\n",
            i, objects[i]->get_rang(), objects[i]->get_x(), objects[i]->get_y(), objects[i]->get_s());
    }


    // Âûïîëíÿåì øàã
    printf("Executing step...\n");
    make_step(test_map);

    printf("After step:\n");
    m_print(test_map);


    printf("Step completed successfully\n");

    delete test_map;
    return true;
}

// Òåñò ïðîâåðêè îêîí÷àíèÿ èãðû
bool t_map_game_over() {
    // Òåñò 1: Íå âñå îáúåêòû îäíîãî òèïà
    Map* test_map1 = new Map(1, 1, 1);
    bool game_over1 = test_map1->if_game_over();
    assert(game_over1 == false);
    printf("Game with multiple types: %s\n", game_over1 ? "OVER" : "CONTINUE");

    // Òåñò 2: Òîëüêî âîëêè
    Map* test_map2 = new Map(2, 0, 0);
    bool game_over2 = test_map2->if_game_over();
    printf("Game with only wolves: %s\n", game_over2 ? "OVER" : "CONTINUE");

    // Òåñò 3: Òîëüêî çàéöû  
    Map* test_map3 = new Map(0, 2, 0);
    bool game_over3 = test_map3->if_game_over();
    printf("Game with only rabbits: %s\n", game_over3 ? "OVER" : "CONTINUE");

    // Òåñò 4: Òîëüêî êàïóñòà
    Map* test_map4 = new Map(0, 0, 2);
    bool game_over4 = test_map4->if_game_over();
    printf("Game with only coles: %s\n", game_over4 ? "OVER" : "CONTINUE");

    delete test_map1;
    delete test_map2;
    delete test_map3;
    delete test_map4;
    return true;
}

// Êîìïëåêñíûé òåñò âñåé êàðòû
bool t_map_comprehensive() {
    printf("=== COMPREHENSIVE MAP TESTS ===\n");

    // Ñîçäàåì êàðòó
    Map* test_map = new Map(2, 3, 2);

    // Òåñò 1: Ïðîâåðÿåì íà÷àëüíîå ñîñòîÿíèå
    printf("\n1. Initial state:\n");
    test_map->print();
    std::vector<MapObj*> initial_objects = test_map->get_obj();
    assert(initial_objects.size() == 7); // 2 + 3 + 2

    // Òåñò 2: Âûïîëíÿåì íåñêîëüêî øàãîâ
    printf("\n2. Simulating 5 steps:\n");
    for (int i = 0; i < 5; i++) {
        printf("Step %d:\n", i + 1);
        test_map->make_step();
        test_map->print();

        // Ïðîâåðÿåì, ÷òî èãðà íå çàêîí÷èëàñü ðàíüøå âðåìåíè
        if (i < 4) {
            assert(test_map->if_game_over() == false);
        }
    }

    // Òåñò 3: Óíè÷òîæàåì íåñêîëüêî îáúåêòîâ
    printf("\n3. Testing object destruction:\n");
    std::vector<MapObj*> objects_before_kill = test_map->get_obj();
    if (objects_before_kill.size() > 2) {
        // Óíè÷òîæàåì ïåðâûé îáúåêò
        test_map->kill(objects_before_kill[0]);
        std::vector<MapObj*> objects_after_kill = test_map->get_obj();
        printf("Objects after kill: %zu -> %zu\n",
            objects_before_kill.size(), objects_after_kill.size());
    }

    // Òåñò 4: Ïðîâåðÿåì êîíå÷íîå ñîñòîÿíèå
    printf("\n4. Final state:\n");
    test_map->print();
    bool final_game_state = test_map->if_game_over();
    printf("Game over: %s\n", final_game_state ? "YES" : "NO");

    delete test_map;
    printf("Comprehensive map tests completed\n");
    return true;
}

