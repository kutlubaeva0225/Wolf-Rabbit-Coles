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
	if (!can_be_moved() || m == nullptr) { //капуста никого не ищет 
		return nullptr;
	}
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	for (MapObj* target : m->get_obj()) { //get_obj возвращает всех все объекты карты. Будет брать из контейнера справа. Const, чтобы цель не менять по ссылке
		if (this->get_rang() - target->get_rang() == 1) { //интеретсны только ниже рангом, но на 1. Волк капусту не ест
			int dx = abs(target->get_x() - x);
			int dy = abs(target->get_y() - y);
			if (dx > MAX_COOR / 2) dx = MAX_COOR - dx; //если расстояние больше чем половина карты, то измеряем с другой стороны
			if (dy > MAX_COOR / 2) dy = MAX_COOR - dy;
			int distance = dx + dy; // измеряем расстояние по манх-й норме
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
#if 1 //временная версия с отладкой 
bool MapObj::chase_targ(MapObj* target, Map* m) {
	if (!can_be_moved() || target == nullptr || m == nullptr) {
		printf("DEBUG: chase_targ - invalid parameters\n");
		return false;
	}

	int targ_x = target->get_x();
	int targ_y = target->get_y();

	printf("DEBUG: BEFORE CALC - Current: (%d,%d), Target: (%d,%d)\n", x, y, targ_x, targ_y);

	int dx = targ_x - x;
	int dy = targ_y - y;

	printf("DEBUG: RAW DIFF - dx=%d, dy=%d\n", dx, dy);

	if (dx > MAX_COOR / 2) {
		dx = dx - MAX_COOR;
		printf("DEBUG: Adjusted dx (tor) from %d to %d\n", dx + MAX_COOR, dx);
	}
	else if (dx < -MAX_COOR / 2) {
		dx = dx + MAX_COOR;
		printf("DEBUG: Adjusted dx (tor) from %d to %d\n", dx - MAX_COOR, dx);
	}

	if (dy > MAX_COOR / 2) {
		dy = dy - MAX_COOR;
		printf("DEBUG: Adjusted dy (tor) from %d to %d\n", dy + MAX_COOR, dy);
	}
	else if (dy < -MAX_COOR / 2) {
		dy = dy + MAX_COOR;
		printf("DEBUG: Adjusted dy (tor) from %d to %d\n", dy - MAX_COOR, dy);
	}

	printf("DEBUG: AFTER TOR ADJUSTMENT - dx=%d, dy=%d\n", dx, dy);

	// Двигаемся к цели (ограничение будет в move_on)
	return move_on(dx, dy, m, true);
}
#endif

#if 0
bool MapObj::chase_targ(MapObj* target, Map* m) {
	if (!can_be_moved() || target == nullptr || m == nullptr) {
		return false; //капуста никого не ловит
	}
	int targ_x = target->get_x();
	int targ_y = target->get_y();

	int dx = targ_x - x;
	int dy = targ_y - y;

	if (dx > MAX_COOR / 2) dx -= MAX_COOR; //отриц заначение dx движение влево, если короче слева - зайдем слева
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR; // если справа ближе - пойдем справа

	if (dy > MAX_COOR / 2) dy -= MAX_COOR; //отриц заначение dx движение вниз, если короче слева - зайдем снизу
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // если сверху ближе - пойдем сверху

	move_on(dx, dy, m, true); //двигаемя пропуская фазу преследования
	return true;
}
#endif
bool MapObj::eat(Map* m) {
	if (m == nullptr) return false;
	MapObj* target = find_targ(1, m);
	if (!can_be_moved() || target == nullptr) {
		return false; //капуста никого не ест
	}
	m->kill(target);
	stamina += PLUS_S;
	return true;
}
bool MapObj::move_on(int dx, int dy, Map* m, bool nskip_chase = false) { //dx, dy предлагаемые параметры перемещения
	if (m == nullptr) return false;
	if (!can_be_moved()) return false;
	if (dx > MAX_SHIFT) dx = MAX_SHIFT; //не можем переместиться дальше, чем можем
	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;
	if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;

	if (nskip_chase && find_targ(0, m) != nullptr) { //если заяц по близости есть, будем его преследовать
		return chase_targ(find_targ(0, m), m);
	}

	// Рассчитываем новые координаты
	int new_x = x + dx;
	int new_y = y + dy;

	// Обрабатываем выход за границы (тор)
	if (new_x < 0) new_x = MAX_COOR + new_x;
	else if (new_x > MAX_COOR) new_x = new_x - MAX_COOR - 1; // не пропускаем нулевую клетку

	if (new_y < 0) new_y = MAX_COOR + new_y;
	else if (new_y > MAX_COOR) new_y = new_y - MAX_COOR - 1; // не пропускаем нулевую клетку

	// Применяем новые координаты
	stamina -= (abs(x - new_x) + abs(y - new_y)) * EFFORT;
	if (!is_alive()) {
		m->kill(this);
		return false;
	}
	x = new_x;
	y = new_y;
	return true;
}