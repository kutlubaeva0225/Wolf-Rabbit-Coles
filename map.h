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
	Map(int w, int r, int c);
	void print() const; // ����� ���������� ��������� ���������� � �����
	void kill(MapObj* target); //����� ����
	void make_step(); //��������� ���� ��� ���� 
	bool if_game_over(); // ��������� �������� �� ����, ����� ����� ������ ���� ����� 
	//Map* copy(Map* m); 
	std::vector<MapObj*> get_obj() const; //���������� ��������� �������� �����
	~Map(); //����� ����������, ����� �� ���� ������ ������ 
};

#endif