#include "wolf.h"
#include "map.h"
#include <cassert>

#ifndef TEST_WOLF_H_
#define TEST_WOLF_H_

// Òåñò ñîçäàíèÿ âîëêà 
bool t_create_wolf() {
    Wolf* wolf = new Wolf(5, 5, START_S, 2, 0.5);
    assert(wolf->get_x() == 5);
    assert(wolf->get_y() == 5);
    assert(wolf->get_s() == START_S);
    assert(wolf->get_rang() == 2);
    assert(wolf->get_ag() == 0.5);
    printf("Wolf created correctly\n");
    delete wolf;
    return true;
}

// Òåñò îáíîâëåíèÿ àãðåññèè 
bool t_update_agg() {
    Wolf* wolf = new Wolf(5, 5, START_S, 2, 0.5);
    double old_agg = wolf->get_ag();
    wolf->update_agg();
    double new_agg = wolf->get_ag();
    assert(new_agg >= 0 && new_agg <= 1);
    printf("Wolf aggression updated: %.2f -> %.2f\n", old_agg, new_agg);
    delete wolf;
    return true;
}

// Òåñò ïîâåäåíèÿ âîëêà íà ÊÎÍÊÐÅÒÍÎÉ êàðòå
bool t_wolf_on_map(Map* test_map) {
    printf("Testing wolf behavior on specific map...\n");

    // Íàõîäèì âîëêîâ íà êàðòå
    std::vector<MapObj*> objects = test_map->get_obj();
    int wolf_count = 0;

    for (MapObj* obj : objects) {
        if (Wolf* wolf = dynamic_cast<Wolf*>(obj)) {
            wolf_count++;
            printf("Testing wolf %d at position (%d, %d)\n",
                wolf_count, wolf->get_x(), wolf->get_y());

            // Òåñòèðóåì áàçîâûå ñâîéñòâà
            assert(wolf->get_rang() == 2);
            assert(wolf->get_ag() >= 0 && wolf->get_ag() <= 1);

            // Òåñòèðóåì ìåòîä wanna_eat ñ ÊÎÍÊÐÅÒÍÎÉ êàðòîé
            bool eat_result = wolf->wanna_eat(test_map);
            printf("Wolf wanna_eat result: %s\n", eat_result ? "true" : "false");

            // Òåñòèðóåì îáíîâëåíèå àãðåññèè
            double old_agg = wolf->get_ag();
            wolf->update_agg();
            assert(wolf->get_ag() >= 0 && wolf->get_ag() <= 1);
            printf("Aggression updated: %.2f -> %.2f\n", old_agg, wolf->get_ag());
        }
    }

    printf("Tested %d wolfs on map\n", wolf_count);
    return true;
}

#endif




