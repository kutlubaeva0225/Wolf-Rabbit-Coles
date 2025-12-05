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
	// Базовые проверки
	if (!can_be_moved() || m == nullptr) {
		return nullptr;
	}
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	// Перебор всех объектов на карте
	for (MapObj* target : m->get_obj()) {

		// 1. Не проверяем сами себя
		if (target == this) continue;

		// 2. Проверка ранга (строго на 1 меньше нашего)
		if (this->get_rang() - target->get_rang() == 1) {

			// Расчет координат
			int dx = abs(target->get_x() - x);
			int dy = abs(target->get_y() - y);

			// Учет "круглого мира" (Тор)
			if (dx > MAX_COOR / 2) dx = MAX_COOR - dx;
			if (dy > MAX_COOR / 2) dy = MAX_COOR - dy;

			int distance = dx + dy;

			// 3. Проверка дистанции
			if (distance <= r) {
				//printf("Me %d with the pos (%d, %d) found target %d at the pos (%d, %d) to %d\n",this->get_rang(), this->get_x(), this->get_y(), target->get_rang(), target->get_x(), target->get_y(), i);
				return target; // Нашли цель — сразу возвращаем её
			}
			// Если далеко — просто идем дальше по циклу (continue не обязателен, т.к. конец блока)
		}

	}

	return nullptr;
}

bool MapObj::chase_targ(MapObj* target, Map* m) {
	if (!can_be_moved() || target == nullptr || m == nullptr) {
		return false; //капуста никого не ловит
	}

	int dx = target->get_x() - x;
	int dy = target->get_y() - y;

	if (dx > MAX_COOR / 2) dx -= MAX_COOR; //отриц заначение dx движение влево, если короче слева - зайдем слева
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR;  // если справа ближе - пойдем справа

	if (dy > MAX_COOR / 2) dy -= MAX_COOR; //отриц заначение dx движение вниз, если короче слева - зайдем снизу
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // если сверху ближе - пойдем сверху

	// Движение только на один шаг к цели
	if (dx != 0) dx = (dx > 0) ? 1 : -1;
	if (dy != 0) dy = (dy > 0) ? 1 : -1;

	return move_on(dx, dy, m, true);  //двигаемя пропуская фазу преследования
}


bool MapObj::eat(Map* m) {
	if (m == nullptr) return false;
	MapObj* target = find_targ(1, m);
	if (!can_be_moved() || target == nullptr) {
		return false; //капуста никого не ест
	}
	//printf("the target %d  at position (%d, %d), was killed\n", target->get_rang(), target->get_x(), target->get_y());
	m->kill(target);
	stamina += PLUS_S;
	return true;
}

bool MapObj::move_on(int dx, int dy, Map* m, bool skip_chase_logic = true) {
	if (m == nullptr) return false;
	if (!can_be_moved()) return false;

	// Ограничиваем дальность хода
	if (dx > MAX_SHIFT) dx = MAX_SHIFT;
	else if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;

	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	else if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;

	// --- ИСПРАВЛЕНИЕ 1: Логика преследования ---
	// В chase_targ вы вызываете move_on с false, а тут проверяете !nskip. 
	// Это вызывало бы бесконечный цикл.
	// Здесь мы проверяем: если мы НЕ в режиме выполнения погони (skip_chase_logic == false), 
	// то ищем цель.
	if (!skip_chase_logic && find_targ(0, m) != nullptr) {
		return chase_targ(find_targ(0, m), m);
	}

	// Рассчитываем новые координаты
	int new_x = x + dx;
	int new_y = y + dy;

	// Размер карты (если координаты 0..15, то размер 16)
	int map_size = MAX_COOR + 1;

	// --- ИСПРАВЛЕНИЕ 2: Правильный Тор (зацикливание) ---
	// Ваша старая формула сдвигала клетки неправильно при переходе через 0
	if (new_x < 0) new_x += map_size;
	else if (new_x > MAX_COOR) new_x -= map_size;

	if (new_y < 0) new_y += map_size;
	else if (new_y > MAX_COOR) new_y -= map_size;

	// --- ИСПРАВЛЕНИЕ 3 (ГЛАВНОЕ): Расчет стамины ---
	// Считаем расход по РЕАЛЬНО пройденному пути (dx, dy), а не по скачку координат
	int cost = (abs(dx) + abs(dy)) * EFFORT;
	stamina -= cost;

	if (!is_alive()) {
		m->kill(this); // Умер от усталости
		return false;
	}

	x = new_x;
	y = new_y;
	return true;
}


//перевод с Си

extern "C" {
	int get_s(MapObj* obj) {
		return obj->get_s();
	}
	int give_s(MapObj* obj, int ds) {
		if (ds + obj->get_s() > MAX_STAMINA || ds + obj->get_s() < 0) {
			return 1; //ошибка
		}
		else {
			obj->give_s(ds);
			return 0; //успех 
		}
	}
	int move_on(MapObj* obj, int dx, int dy, Map* m, int mode) {
		// mode == 1 -> ЛОВИТЬ
		// mode == 0 -> ПРОСТО ИДТИ (не ловить)

		if (obj == nullptr || m == nullptr) return 1; //ошибка 

		if (mode == 1) {
			// Мы хотим ЛОВИТЬ. Значит, "пропуск погони" должен быть false.
			obj->move_on(dx, dy, m, false);
		}
		else {
			// Мы хотим просто идти (НЕ ЛОВИТЬ). Значит, "пропуск погони" должен быть true.
			obj->move_on(dx, dy, m, true);
		}

		return 0;
	}
}



