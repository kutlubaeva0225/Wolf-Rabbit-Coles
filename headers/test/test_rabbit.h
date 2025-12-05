#include "rabbit.h"
#include "map.h"
#include <cassert>

#ifndef TEST_RABBIT_H_
#define TEST_RABBIT_H_

// Тест создания зайца (без карты)
bool t_create_rabbit();
// Тест поведения зайца на КОНКРЕТНОЙ карте
bool t_rabbit_on_map(Map* test_map);

#endif
