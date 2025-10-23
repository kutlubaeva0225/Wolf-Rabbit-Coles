#include <cstdio>
#include <cstdlib>
#include <cmath>



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
	bool move_on(int dx, int dy, Map* map, bool nskip_chase); //��� ���� ����, ���� ����� ��������, � ������ ������ �� ����� ��������������, ���� �� ������ ���������� ���� ������ 
	MapObj* find_targ(int i, Map* map); //// ���� i = 0, �� � ���� ���������, ���� i = 1, �� ���� ����� � ���� �������. ��� ������� ������ �� ���������� 
	bool chaise_targ(MapObj* target); //��� ������� ����� ������ ����������� 
	bool eat(Map* map);// ������� �� ������ ������ 
	bool is_alive() const;
	virtual bool give_s(int ds); // ���������� �����, �����, � ������� ������������ � ����� ������ ��� ������ ���� � �� �� �������� 
};

MapObj::MapObj(int s_x, int s_y, int s, int r) : x(s_x), y(s_y), stamina(s), rang(r) {
	if (s_x > MAX_COOR) x = MAX_COOR;
	if (s_x < 0) x = 0;
	if (s_y > MAX_COOR) y = MAX_COOR;
	if (s_y < 0) y = 0;

}

bool MapObj::can_be_moved() {
	true;
}
int MapObj::get_x() const {
	return x;
}
int MapObj::get_y() const {
	return y;
}
int MapObj::get_rang() const {
	return rang;
}
int MapObj::get_s() const {
	return stamina;
}
bool MapObj::is_alive() const {
	return stamina > 0;
}
bool MapObj::give_s(int ds) {
	if
	if (ds + stamina > 1 || ds + stamina < 0) {
		return false;
	}
	else {
		stamina += ds;
		return true;
	}

}
MapObj* MapObj::find_targ(int i, Map* map) {
	if (!can_be_moved() || map == nulptr) { //������� ������ �� ���� 
		return nullptr;
	}
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	for (const auto& target : map.get_obj()) { //get_obj ���������� ���� ��� ������� �����. ����� ����� �� ���������� ������. Const, ����� ���� �� ������ �� ������
		if (this->get_rang() - target->get_rang() == 1 ) { //���������� ������ ���� ������, �� �� 1. ���� ������� �� ���
			int dx = abs(target->get_x() - x);
			int dy = abs(target->get_y() - y);
			if (dx > MAX_COOR / 2) dx = MAX_COOR - dx; //���� ���������� ������ ��� �������� �����, �� �������� � ������ �������
			if (dy > MAX_COOR / 2) dx = MAX_COOR - dy;
			int distance = dx + dy; // �������� ���������� �� ����-� �����
			if (distance <= r) {
				return target;
			}
			else {
				return nullptr;
			}
		}
		else return nullptr;
	}
}
bool MapObj::chase_targ(MapObj* target) {
	if (!can_be_moved() || target == nullptr) {
		return false; //������� ������ �� �����
	}
	int targ_x = target->get_x();
	int targ_y = target->get_y();

	int dx = x - targ_x;
	int dy = y - targ_y;

	if (dx > MAX_COOR / 2) dx -= -MAX_COOR; //����� ��������� dx �������� �����, ���� ������ ����� - ������ �����
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR; // ���� ������ ����� - ������ ������

	if (dy > MAX_COOR / 2) dy -= -MAX_COOR; //����� ��������� dx �������� ����, ���� ������ ����� - ������ �����
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // ���� ������ ����� - ������ ������

	move_on(dx, dy, true); //�������� ��������� ���� �������������
	return true;
}

bool MapObj::eat(Map* map) {
	if (map == nulptr) return false;
	MapObj* target = find_target(1);
	if (!can_be_moved() || target == nullptr ) {
		return false; //������� ������ �� ���
	}
	map.kill(target);
	stamina += PLUS_S
	return true;
}
bool MapObj::move_on(int dx, int dy, Map* map, bool nskip_chase = false) { //dx, dy ������������ ��������� �����������
	if (map == nulptr) return false;
	if (!can_be_moved()) return false;
	if (dx > MAX_SHIFT) dx = MAX_SHIFT; //�� ����� ������������� ������, ��� �����
	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;
	if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;

	if (nskip_chase && find_targ(0) != nullptr ) { //���� ���� �� �������� ����, ����� ��� ������������
		return chaise_targ(find_targ(0));
	}

	// ������������ ����� ����������
	int new_x = x + dx;
	int new_y = y + dy;

	// ������������ ����� �� ������� (���)
	if (new_x < 0) new_x = MAX_COOR + new_x;
	else if (new_x > MAX_COOR) new_x = new_x - MAX_COOR - 1; // �� ���������� ������� ������

	if (new_y < 0) new_y = MAX_COOR + new_y;
	else if (new_y > MAX_COOR) new_y = new_y - MAX_COOR - 1; // �� ���������� ������� ������

	// ��������� ����� ����������
	stamina -= (abs(x - new_x) + abs(y - new_y)) * EFFORT;
	if (!is_alive()) {
		map.kill(this);
		return;
	}
	x = new_x;
	y = new_y;
	return false;
}
#endif


