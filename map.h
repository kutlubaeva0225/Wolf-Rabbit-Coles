#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mapobj.h"

#ifndef MAP_H_
#define MAP_H_
#define MAX_N_OBJ 10
#define MAX_STAMINA 20
#define PLUS_S 5 //������� ���� ��� ���� �������
#define EFFORT 1 //������� ��� �� ����������� �� ������� ������
#define MAX_SHIFT 3 //������������ ����������� �� ���� ��� �������������
#define R_VIEW 4 //������ ������ 
#define R_DRAP 1 //������ ������� ����
#define MAX_COOR 15 //������ ����� 
#define START_S MAX_STAMINA / 2

class Map {
private: 
	MapObj** objects; //��� ������ ��� ���� ���������� �������� �����
	int wolfs; //����� ������ 
	int rabbits; //����� ������  
	int coles;//����� ������
	int obj_num;  // ����� �������� � �������
	int curr_time; // ������� ����� 
public:
	void print() const; // ����� ���������� ��������� ���������� � �����
	void kill(MapObj* target); //����� ����
	void make_step(); //��������� ���� ��� ���� 
	bool if_game_over(); // ��������� �������� �� ����, ����� ����� ������ ���� ����� 
	//Map* copy(Map* m); (???)
	std::vector<MapObj*> get_obj() const; //���������� ��������� �������� �����
	~Map(); //����� ����������, ����� �� ���� ������ ������ 
};

Map::Map(int w, int r, int c) : wolfs(w), rabbits(r), coles(c), obj_num(0), curr_time(0) {
	if (w < 0 || w > MAX_N_OBJ / 3) w = MAX_N_OBJ / 6;
	if (r < 0 || r > MAX_N_OBJ / 3) r = MAX_N_OBJ / 6;
	if (c < 0 || c > MAX_N_OBJ / 3) c = MAX_N_OBJ / 6;
	int total_n_obj = w + r + c;
	MapObj** objects = new MapObj*[total_n_obj]; //����� ��� ���������� ������� �����
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
		delete objects[i];  // ������� ������ ���������
	}
	delete[] objects;       // ������� ������ ����������
}


void Map::print() const {
	printf("���. �����: %d\n", curr_time);
	printf("�������� �����: %d\n", obj_num);
	printf("�����: %d, �����: %d, �������: %d\n", wolfs, rabbits, coles);
}

void Map::kill(MapObj* target) {
	if (target == nullptr) return;
	for (int i = 0; i < obj_num; ++i) {
		if (objects[i] == target) {
			delete objects[i]; //������� ��������� ����
			for (int j = i; j < obj_num; ++j) { 
				objects[j] = objects[j + 1]; //�������� ��� ����������� ��������� � ������� ����� ��������� ����
			}
			if (dynamic_cast<Wolf*>(target)) wolfs--; //���������� ��������� 
			else if (dynamic_cast<Rabbit*>(target)) rabbits--;
			else if (dynamic_cast<Cole*>(target)) coles--;
			obj_num--;
			return;
		}
	}
}
std::vector<MapObj*> Map::get_obj() const { 
	return std::vector<MapObj*>(objects, objects + object_num); //������� ������� ... ��������� 
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