#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mapobj.h"

#ifndef MAP_H_
#define MAP_H_
#define MAX_N_OBJ 10
#define MAX_STAMINA 20
#define PLUS_S 5 //сколько цель сил даст объекту
#define EFFORT 1 //затрата сил на перемещение на единицу длинны
#define MAX_SHIFT 3 //максимальное перемещение за один шаг моделирования
#define R_VIEW 4 //радиус обзора 
#define R_DRAP 1 //радиус захвата пищи
#define MAX_COOR 15 //размер карты 
#define START_S MAX_STAMINA / 2

class Map {
private: 
	MapObj** objects; //дин массив для всех указателей объектов карты
	int wolfs; //число волков 
	int rabbits; //число зайцев  
	int coles;//число капуст
	int obj_num;  // число объектов в массиве
	int curr_time; // текущее время 
public:
	Map(int w, int r, int c);
	void print() const; // вывод отладочной текстовой информации о карте
	void kill(MapObj* target); //убить цель
	void make_step(); //совершить один шаг игры 
	bool if_game_over(); // проверяет окончена ли игра, когда выжил только один класс 
	//Map* copy(Map* m); 
	std::vector<MapObj*> get_obj() const; //возвращает контейнер объектов карты
	~Map(); //пишем деструктор, чтобы не было утечки памяти 
};

#endif