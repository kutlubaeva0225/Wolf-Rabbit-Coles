#include "cole.h"
#include "map.h"
#include <cassert>

#ifndef TEST_COLE_H_
#define TEST_COLE_H_

// Тест создания капусты (без карты)
bool t_create_cole();

// Тест поведения капусты на КОНКРЕТНОЙ карте
bool t_cole_on_map(Map* test_map);

#endif