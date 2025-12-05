#include "map.h"
#include <cassert>

#ifndef TEST_MAP_H_
#define TEST_MAP_H_


bool t_create_map();// Тест создания карты
bool t_map_get_objects();// Тест получения объектов с карты
bool t_map_kill_objects(); // Тест уничтожения объектов на карте
bool t_map_make_step(); // Тест шага моделирования
bool t_map_game_over(); // Тест проверки окончания игры
bool t_map_comprehensive();// Комплексный тест всей карты

#endif
