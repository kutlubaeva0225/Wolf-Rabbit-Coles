#include "wolf.h"
#include "map.h"
#include <cassert>

#ifndef TEST_WOLF_H_
#define TEST_WOLF_H_

// Тест создания волка 
bool t_create_wolf();
// Тест обновления агрессии 
bool t_update_agg();
// Тест поведения волка на КОНКРЕТНОЙ карте
bool t_wolf_on_map(Map* test_map);
#endif




