#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "mapobj.h"
#include "map.h"

MapObj::MapObj(int s_x, int s_y, int s, int r) : x(s_x), y(s_y), stamina(s), rang(r) {
	if (s_x > MAX_COOR) x = MAX_COOR;
	if (s_x < 0) x = 0;
	if (s_y > MAX_COOR) y = MAX_COOR;
	if (s_y < 0) y = 0;

}

bool MapObj::can_be_moved() const {
	return true;
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
	if (ds + stamina > MAX_STAMINA || ds + stamina < 0) {
		return false;
	}
	else {
		stamina += ds;
		return true;
	}

}
MapObj* MapObj::find_targ(int i, Map* m) {
	if (!can_be_moved() || m == nullptr) { //������� ������ �� ���� 
		return nullptr;
	}
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	for (MapObj* target : m->get_obj()) { //get_obj ���������� ���� ��� ������� �����. ����� ����� �� ���������� ������. Const, ����� ���� �� ������ �� ������
		if (this->get_rang() - target->get_rang() == 1) { //���������� ������ ���� ������, �� �� 1. ���� ������� �� ���
			int dx = abs(target->get_x() - x);
			int dy = abs(target->get_y() - y);
			if (dx > MAX_COOR / 2) dx = MAX_COOR - dx; //���� ���������� ������ ��� �������� �����, �� �������� � ������ �������
			if (dy > MAX_COOR / 2) dy = MAX_COOR - dy;
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
	return nullptr;
}

bool MapObj::chase_targ(MapObj* target, Map* m) {
	if (!can_be_moved() || target == nullptr || m == nullptr) {
		return false; //������� ������ �� �����
	}

	int dx = target->get_x() - x;
	int dy = target->get_y() - y;

	if (dx > MAX_COOR / 2) dx -= MAX_COOR; //����� ��������� dx �������� �����, ���� ������ ����� - ������ �����
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR;  // ���� ������ ����� - ������ ������

	if (dy > MAX_COOR / 2) dy -= MAX_COOR; //����� ��������� dx �������� ����, ���� ������ ����� - ������ �����
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // ���� ������ ����� - ������ ������

	// �������� ������ �� ���� ��� � ����
	if (dx != 0) dx = (dx > 0) ? 1 : -1;
	if (dy != 0) dy = (dy > 0) ? 1 : -1;

	return move_on(dx, dy, m, false);  //�������� ��������� ���� �������������
}


bool MapObj::eat(Map* m) {
	if (m == nullptr) return false;
	MapObj* target = find_targ(1, m);
	if (!can_be_moved() || target == nullptr) {
		return false; //������� ������ �� ���
	}
	m->kill(target);
	stamina += PLUS_S;
	return true;
}
bool MapObj::move_on(int dx, int dy, Map* m, bool nskip_chase = true) { //dx, dy ������������ ��������� �����������
	if (m == nullptr) return false;
	if (!can_be_moved()) return false;
	if (dx > MAX_SHIFT) dx = MAX_SHIFT; //�� ����� ������������� ������, ��� �����
	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;
	if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;

	if (nskip_chase && find_targ(0, m) != nullptr) { //���� ���� �� �������� ����, ����� ��� ������������
		return chase_targ(find_targ(0, m), m);
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
		m->kill(this);
		return false;
	}
	x = new_x;
	y = new_y;
	return true;
}