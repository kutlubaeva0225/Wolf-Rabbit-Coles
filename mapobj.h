#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>




#ifndef MAPOBJ_H_
#define MAPOBJ_H_

#define MAX_N_OBJ 10
#define MAX_STAMINA 20
#define PLUS_S 5 //������� ���� ��� ���� �������
#define EFFORT 1 //������� ��� �� ����������� �� ������� ������
#define MAX_SHIFT 3 //������������ ����������� �� ���� ��� �������������
#define R_VIEW 4 //������ ������ 
#define R_DRAP 1 //������ ������� ����
#define MAX_COOR 15 //������ ����� 
#define START_S MAX_STAMINA / 2

class Map;

class MapObj {
private: 
	int x; int y; 
protected:
	int stamina;  int rang; //rang ��������� � ���� �������: B > � > �. ���� r1 = r2 + 1, �� 1 �������� 2 r_K = 0, � ������� ������� �� ����� r = 0 � ���� ������������ 
public:
	MapObj(int x, int y, int stamina, int rang);
	virtual bool can_be_moved() const; //���������� � ������� �� false
	int get_x() const;
	int get_y() const;
	int get_rang() const;
	int get_s() const;
	bool move_on(int dx, int dy, Map* m, bool nskip_chase); //��� ���� ����, ���� ����� ��������, � ������ ������ �� ����� ��������������, ���� �� ������ ���������� ���� ������ 
	MapObj* find_targ(int i, Map* m); //// ���� i = 0, �� � ���� ���������, ���� i = 1, �� ���� ����� � ���� �������. ��� ������� ������ �� ���������� 
	bool chase_targ(MapObj* target, Map* m); //��� ������� ����� ������ ����������� 
	bool eat(Map* m);// ������� �� ������ ������ 
	bool is_alive() const;
	virtual bool give_s(int ds); // ���������� �����, �����, � ������� ������������ � ����� ������ ��� ������ ���� � �� �� �������� 
};
#endif


