#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mapobj.h"
#include "map.h"
#include "wolf.h"
#include "rabbit.h"
#include "cole.h"


Map::Map(int w, int r, int c) : wolfs(w), rabbits(r), coles(c), obj_num(0), curr_time(0) {
	if (w < 0 || w > MAX_N_OBJ / 3) w = MAX_N_OBJ / 6;
	if (r < 0 || r > MAX_N_OBJ / 3) r = MAX_N_OBJ / 6;
	if (c < 0 || c > MAX_N_OBJ / 3) c = MAX_N_OBJ / 6;
	int total_n_obj = w + r + c;
	objects = new MapObj*[total_n_obj]; //����� ��� ���������� ������� �����
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
		delete objects[i];  // ������� ������ ���������
	}
	delete[] objects;       // ������� ������ ����������
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
			delete objects[i]; //������� ��������� ����
			objects[i] = nullptr;
			for (int j = i; j < obj_num - 1; ++j) {
				objects[j] = objects[j + 1]; //�������� ��� ����������� ��������� � ������� ����� ��������� ����
			}
			objects[obj_num - 1] = nullptr;
			if (target_rang == 2) wolfs--;        // ����
			else if (target_rang == 1) rabbits--; // ����
			else if (target_rang == 0) coles--;   // �������
			obj_num--;
			return;
		}
	}
}
std::vector<MapObj*> Map::get_obj() const {
	return std::vector<MapObj*>(objects, objects + obj_num); //������� ������� ... ��������� 
}

void Map::make_step() {
	std::vector<MapObj*> snapshot = get_obj();

	for (MapObj* obj : snapshot) {

		// �������� ��� ������ ��� ���
		bool alive = false;
		for (int i = 0; i < obj_num; i++) {
			if (objects[i] == obj) {
				alive = true;
				break;
			}
		}
		if (!alive) continue;

		if (obj->can_be_moved()) {
			obj->move_on(rand() % MAX_SHIFT, rand() % MAX_SHIFT, this, false);

			// ����� move_on ������ �������� ����� ���� ����
			alive = false;
			for (int i = 0; i < obj_num; i++) {
				if (objects[i] == obj) {
					alive = true;
					break;
				}
			}
			if (!alive) continue;

			obj->eat(this);
		}
		else {
			obj->give_s(1);
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
