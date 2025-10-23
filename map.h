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
	void print() const; // вывод отладочной текстовой информации о карте
	void kill(MapObj* target); //убить цель
	void make_step(); //совершить один шаг игры 
	bool if_game_over(); // проверяет окончена ли игра, когда выжил только один класс 
	//Map* copy(Map* m); (???)
	std::vector<MapObj*> get_obj() const; //возвращает контейнер объектов карты
	~Map(); //пишем деструктор, чтобы не было утечки памяти 
};

Map::Map(int w, int r, int c) : wolfs(w), rabbits(r), coles(c), obj_num(0), curr_time(0) {
	if (w < 0 || w > MAX_N_OBJ / 3) w = MAX_N_OBJ / 6;
	if (r < 0 || r > MAX_N_OBJ / 3) r = MAX_N_OBJ / 6;
	if (c < 0 || c > MAX_N_OBJ / 3) c = MAX_N_OBJ / 6;
	int total_n_obj = w + r + c;
	MapObj** objects = new MapObj*[total_n_obj]; //место для указателей объктов карты
	for (int i = 0; i < wolfs; ++i) {
		objects[obj_num] = new Wolf(rand() % MAX_COOR, rand() % MAX_COOR, START_S, 2, (double)rand() / RAND_MAX);
		obj_num++;
	}
	for (int i = 0; i < rabbits; ++i) {
		objects[obj_num] = new Rabbit(rand() % MAX_COOR, rand() % MAX_COOR, START_S, 1);
		obj_num++;
	}
	for (int i = 0; i < rabbits; ++i) {
		objects[obj_num] = new Rabbit(rand() % MAX_COOR, rand() % MAX_COOR, 1, 0);
		obj_num++;
	}
}
Map::~Map() {
	for (int i = 0; i < object_num; i++) {
		delete objects[i];  // удаляем каждый указатель
	}
	delete[] objects;       // удаляем массив указателей
}


void Map::print() const {
	printf("Тек. время: %d\n", curr_time);
	printf("Выжившие особи: %d\n", obj_num);
	printf("Волки: %d, Зайцы: %d, Капуста: %d\n", wolfs, rabbits, coles);
}

void Map::kill(MapObj* target) {
	if (target == nullptr) return;
	for (int i = 0; i < obj_num; ++i) {
		if (objects[i] == target) {
			delete objects[i]; //удалили указатель цели
			for (int j = i; j < obj_num; ++j) { 
				objects[j] = objects[j + 1]; //сдвинули все последующие указатели в массиве после удаленной цели
			}
			if (dynamic_cast<Wolf*>(target)) wolfs--; //подправили константы 
			else if (dynamic_cast<Rabbit*>(target)) rabbits--;
			else if (dynamic_cast<Cole*>(target)) coles--;
			obj_num--;
			return;
		}
	}
}
std::vector<MapObj*> Map::get_obj() const { 
	return std::vector<MapObj*>(objects, objects + object_num); //первыый элемент ... последний 
}

void Map::make_step() {
	for (const auto& obj : map.get_obj()) {
		if (obj->can_be_moved()) {
			bool s1 = target->move_on(rand() % MAX_SHIFT, rand() % MAX_SHIFT);
			bool s2 = target->eat();
		}
		else {
			bool s2 = target->give_s(1);
		}
	}
	curr_time++;
}

bool if_game_over() {
	if (wolfs <= 0 && rabbits <= 0) {
		printf("Coles have won! Congratulations!\n");
		return true;
	}
	else if (wolfs <= 0 && coles <= 0) {
		printf("Rabbits have won! Congratulations!\n");
		return true;
	}
	else if (rabbits <= 0 && coles <= 0) {
		printf("Wolfs have won! Congratulations!\n");
		return true;
	}
	else return false;
}


#endif