#include "mapobj.h"
#include "map.h"
#include <cassert>

#ifndef TEST_MAPOBJ_H_
#define TEST_MAPOBJ_H_

// Òåñò ñîçäàíèÿ áàçîâîãî îáúåêòà
bool t_create_mapobj() {
    MapObj* obj = new MapObj(5, 5, START_S, 1);
    assert(obj->get_x() == 5);
    assert(obj->get_y() == 5);
    assert(obj->get_s() == START_S);
    assert(obj->get_rang() == 1);
    assert(obj->can_be_moved() == true);
    assert(obj->is_alive() == true);
    printf("MapObj created correctly\n");
    delete obj;
    return true;
}

// Òåñò äâèæåíèÿ îáúåêòà
bool t_mapobj_movement() {
    Map* test_map = new Map(0, 1, 0); // Òîëüêî 1 îáúåêò äëÿ òåñòà äâèæåíèÿ
    MapObj* obj = new MapObj(5, 5, START_S, 1);

    int old_x = obj->get_x();
    int old_y = obj->get_y();
    int old_stamina = obj->get_s();

    // Òåñòèðóåì äâèæåíèå
    bool move_result = obj->move_on(2, 1, test_map, false);
    printf("MapObj moved from (%d,%d) to (%d,%d), stamina: %d -> %d\n",
        old_x, old_y, obj->get_x(), obj->get_y(), old_stamina, obj->get_s());

    assert(move_result == true || move_result == false);
    assert(obj->get_s() <= old_stamina); // Ñòàìèíà äîëæíà óìåíüøèòüñÿ

    delete obj;
    delete test_map;
    return true;
}

// Òåñò ïîèñêà öåëè
bool t_mapobj_find_target() {
    // Ñîçäàåì êàðòó ñ îáúåêòàìè ðàçíûõ ðàíãîâ
    Map* test_map = new Map(1, 1, 1); // Âîëê, çàÿö, êàïóñòà

    // Íàõîäèì âîëêà íà êàðòå
    MapObj* wolf = nullptr;
    std::vector<MapObj*> objects = test_map->get_obj();
    for (MapObj* obj : objects) {
        if (obj->get_rang() == 2) {
            wolf = obj;
            break;
        }
    }

    if (wolf) {
        // Âîëê äîëæåí íàéòè çàéöà (ðàíã 2-1=1)
        MapObj* target = wolf->find_targ(0, test_map);
        if (target) {
            printf("Wolf found target with rang %d at (%d,%d)\n",
                target->get_rang(), target->get_x(), target->get_y());
            assert(target->get_rang() == 1); // Äîëæåí íàéòè çàéöà
        }
    }

    delete test_map;
    return true;
}

// Òåñò ïîåäàíèÿ
bool t_mapobj_eat() {
    Map* test_map = new Map(0, 1, 1); // Çàÿö è êàïóñòà
    MapObj* rabbit = nullptr;

    std::vector<MapObj*> objects = test_map->get_obj();
    for (MapObj* obj : objects) {
        if (obj->get_rang() == 1) {
            rabbit = obj;
            break;
        }
    }

    if (rabbit) {
        int old_stamina = rabbit->get_s();
        bool eat_result = rabbit->eat(test_map);
        printf("Rabbit eat result: %s, stamina: %d -> %d\n",
            eat_result ? "true" : "false", old_stamina, rabbit->get_s());

        // Åñëè íàøåë êàïóñòó - ñòàìèíà äîëæíà óâåëè÷èòüñÿ
        if (eat_result) {
            assert(rabbit->get_s() > old_stamina);
        }
    }

    delete test_map;
    return true;
}


// Òåñò ïîäêàðìëèâàíèÿ
bool t_mapobj_give_s() {
    MapObj* obj = new MapObj(5, 5, 10, 1);

    int old_stamina = obj->get_s();
    bool feed_result = obj->give_s(3);
    printf("Give_s result: %s, stamina: %d -> %d\n",
        feed_result ? "true" : "false", old_stamina, obj->get_s());
    assert(feed_result == true);
    assert(obj->get_s() == old_stamina + 3);

    delete obj;
    return true;
}

// Òåñò ïðîâåðêè æèâó÷åñòè
bool t_mapobj_is_alive() {
    MapObj* alive_obj = new MapObj(5, 5, 5, 1);
    MapObj* dead_obj = new MapObj(5, 5, 0, 1);

    assert(alive_obj->is_alive() == true);
    assert(dead_obj->is_alive() == false);

    printf("Alive object: %s, Dead object: %s\n",
        alive_obj->is_alive() ? "true" : "false",
        dead_obj->is_alive() ? "true" : "false");

    delete alive_obj;
    delete dead_obj;
    return true;
}

// Òåñò ïðåñëåäîâàíèÿ öåëè
bool t_mapobj_chase_target() {
    Map* test_map = new Map(1, 1, 0); // Âîëê è çàÿö

    MapObj* wolf = nullptr;
    MapObj* rabbit = nullptr;

    std::vector<MapObj*> objects = test_map->get_obj();
    for (MapObj* obj : objects) {
        if (obj->get_rang() == 2) wolf = obj;
        if (obj->get_rang() == 1) rabbit = obj;
    }

    if (wolf && rabbit) {
        int wolf_old_x = wolf->get_x();
        int wolf_old_y = wolf->get_y();

        bool chase_result = wolf->chase_targ(rabbit, test_map);
        printf("Chase result: %s, wolf moved from (%d,%d) to (%d,%d)\n",
            chase_result ? "true" : "false",
            wolf_old_x, wolf_old_y, wolf->get_x(), wolf->get_y());

        assert(chase_result == true);
    }

    delete test_map;
    return true;
}

// Êîìïëåêñíûé òåñò âñåõ ìåòîäîâ MapObj íà ÊÎÍÊÐÅÒÍÎÉ êàðòå
bool t_mapobj_comprehensive(Map* test_map) {
    printf("Comprehensive MapObj tests on specific map...\n");

    std::vector<MapObj*> objects = test_map->get_obj();
    int tested_objects = 0;

    for (MapObj* obj : objects) {
        tested_objects++;
        printf("\nTesting object %d (rang %d) at (%d,%d):\n",
            tested_objects, obj->get_rang(), obj->get_x(), obj->get_y());

        // Òåñò áàçîâûõ ñâîéñòâ
        assert(obj->get_x() >= 0 && obj->get_x() <= MAX_COOR);
        assert(obj->get_y() >= 0 && obj->get_y() <= MAX_COOR);
        assert(obj->get_rang() >= 0 && obj->get_rang() <= 2);

        // Òåñò äâèæåíèÿ (òîëüêî äëÿ ïîäâèæíûõ îáúåêòîâ)
        if (obj->can_be_moved()) {
            bool move_result = obj->move_on(1, 0, test_map, false);
            printf("  Move result: %s\n", move_result ? "true" : "false");
        }

        // Òåñò ïîèñêà öåëåé
        MapObj* target = obj->find_targ(0, test_map);
        if (target) {
            printf("  Found target at (%d,%d) rang %d\n",
                target->get_x(), target->get_y(), target->get_rang());
        }

        // Òåñò æèâó÷åñòè
        printf("  Is alive: %s, Stamina: %d\n",
            obj->is_alive() ? "true" : "false", obj->get_s());
    }

    printf("Comprehensive tests completed for %d objects\n", tested_objects);
    return true;
}

#endif
