#include "mapobj.h"
#include "map.h"
#include <cassert>

#ifndef TEST_MAPOBJ_H_
#define TEST_MAPOBJ_H_

// Тест создания базового объекта
bool t_create_mapobj();
// Тест движения объекта
bool t_mapobj_movement();

// Тест поиска цели
bool t_mapobj_find_target();
// Тест поедания
bool t_mapobj_eat();

// Тест подкармливания
bool t_mapobj_give_s();
// Тест проверки живучести
bool t_mapobj_is_alive();

// Тест преследования цели
bool t_mapobj_chase_target();

// Комплексный тест всех методов MapObj на КОНКРЕТНОЙ карте
bool t_mapobj_comprehensive(Map* test_map);

#endif
