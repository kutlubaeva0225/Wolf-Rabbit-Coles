#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mapobj.h"
#include "map.h"
#include "wolf.h"
#include "rabbit.h"
#include "cole.h"
#include <cstdlib> 
#include <algorithm>



Map::Map(int w, int r, int c) : wolfs(w), rabbits(r), coles(c), obj_num(0), curr_time(0) {
	if (w < 0 || w > MAX_N_OBJ / 3) w = MAX_N_OBJ / 6;
	if (r < 0 || r > MAX_N_OBJ / 3) r = MAX_N_OBJ / 6;
	if (c < 0 || c > MAX_N_OBJ / 3) c = MAX_N_OBJ / 6;
	int total_n_obj = w + r + c;
	objects = new MapObj*[total_n_obj]; //место для указателей объктов карты
	for (int i = 0; i < wolfs; ++i) {
		objects[obj_num] = new Wolf(rand() % MAX_COOR, rand() % MAX_COOR, START_S, 2, (double)rand() / RAND_MAX);
		obj_num++;
	}
	for (int i = 0; i < rabbits; ++i) {
		objects[obj_num] = new Rabbit(rand() % MAX_COOR, rand() % MAX_COOR, START_S, 1);
		obj_num++;
	}
	for (int i = 0; i < coles; ++i) {
		objects[obj_num] = new Cole(rand() % MAX_COOR, rand() % MAX_COOR, 1, 0);
		obj_num++;
	}
}
Map::~Map() {
	for (int i = 0; i < obj_num; i++) {
		delete objects[i];  // удаляем каждый указатель
	}
	delete[] objects;       // удаляем массив указателей
}


void Map::print() const {
	printf("Current time is: %d\n", curr_time);
	printf("Alived: %d\n", obj_num);
	printf("Wolfs: %d, Rabbits: %d, Coles: %d\n", wolfs, rabbits, coles);
}

void Map::kill(MapObj* target) {
	if (target == nullptr) return;
	for (int i = 0; i < obj_num; ++i) {
		if (objects[i] == target) {
			int target_rang = target->get_rang();
			delete objects[i]; //удалили указатель цели
			objects[i] = nullptr;
			for (int j = i; j < obj_num - 1; ++j) {
				objects[j] = objects[j + 1]; //сдвинули все последующие указатели в массиве после удаленной цели
			}
			objects[obj_num - 1] = nullptr;
			if (target_rang == 2) wolfs--;        // Волк
			else if (target_rang == 1) rabbits--; // Заяц
			else if (target_rang == 0) coles--;   // Капуста
			obj_num--;
			return;
		}
	}
}
std::vector<MapObj*> Map::get_obj() const {
	return std::vector<MapObj*>(objects, objects + obj_num); //первыый элемент ... последний 
}



void Map::make_step() {
	// 1. Делаем снимок всех, кто был жив в начале хода
	std::vector<MapObj*> snapshot = get_obj();

	for (MapObj* obj : snapshot) {
		// --- ЗАЩИТА ОТ ЗОМБИ ---
		// Проверяем, существует ли этот указатель в реальном массиве прямо сейчас.
		// Если его съели пару миллисекунд назад, его там уже не будет.

		bool is_alive_now = false;
		for (int i = 0; i < obj_num; i++) {
			if (objects[i] == obj) {
				is_alive_now = true;
				break;
			}
		}

		// Если объекта нет в списке живых — пропускаем его
		if (!is_alive_now) continue;
		// -----------------------

		if (obj->can_be_moved()) {
			// Двигаем
			obj->move_on(rand() % MAX_SHIFT, rand() % MAX_SHIFT, this, false);

			// --- ПРОВЕРКА 2: Не умер ли он во время движения (от голода)? ---
			// Если он умер внутри move_on, его указатель уже невалиден,
			// но нам и не нужно ничего делать, кроме как не вызывать eat.

			bool survived_move = false;
			for (int i = 0; i < obj_num; i++) {
				if (objects[i] == obj) {
					survived_move = true;
					break;
				}
			}
			if (!survived_move) continue;

			// Едим (если выжил)
			obj->eat(this);
		}
		else {
			obj->give_s(1); // Восстанавливаем силы, если стоит
		}
	}

	curr_time++;
}
bool Map::if_game_over() {
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
struct ExportData {
	MapObj* obj_ptr; 
	int type;        // 0=Cole, 1=Rabbit, 2=Wolf
	int x;
	int y;
	int stamina;
};

extern "C" {
	Map* create_map(int w, int r, int c) {
		return new Map(w, r, c);
	}
	void del_map(Map* m) {
		if (m == nullptr) return;
		delete m;
	}
	void m_print(Map* m) {
		if (m == nullptr) return;
		m->print();
	}
	int make_step(Map* m) {
		if (m == nullptr) return 1;
		m->make_step();
		return 0;
	}
	int if_game_over(Map* m) {
		if (m == nullptr) return 1;
		bool b = m->if_game_over();
		if (b) return 0;
		else return 1;
	}

	// Новая функция: заполняет массив данными о всех живых объектах
	// buffer - массив, который подготовит Python
	// max_size - максимальный размер массива
	// Возвращает реальное количество объектов
	int get_snapshot(Map* m, ExportData* buffer, int max_size) {
		if (m == nullptr) return 0;

		std::vector<MapObj*> objs = m->get_obj(); // Получаем вектор
		int count = 0;

		for (MapObj* obj : objs) {
			if (count >= max_size) break; // Защита от переполнения

			buffer[count].obj_ptr = obj;
			buffer[count].type = obj->get_rang(); 
			buffer[count].x = obj->get_x();
			buffer[count].y = obj->get_y();
			buffer[count].stamina = obj->get_s();

			count++;
		}
		return count;
	}
}
