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
	// Áàçîâûå ïðîâåðêè
	if (!can_be_moved() || m == nullptr) {
		return nullptr;
	}
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	// Ïåðåáîð âñåõ îáúåêòîâ íà êàðòå
	for (MapObj* target : m->get_obj()) {

		// 1. Íå ïðîâåðÿåì ñàìè ñåáÿ
		if (target == this) continue;

		// 2. Ïðîâåðêà ðàíãà (ñòðîãî íà 1 ìåíüøå íàøåãî)
		if (this->get_rang() - target->get_rang() == 1) {

			// Ðàñ÷åò êîîðäèíàò
			int dx = abs(target->get_x() - x);
			int dy = abs(target->get_y() - y);

			// Ó÷åò "êðóãëîãî ìèðà" (Òîð)
			if (dx > MAX_COOR / 2) dx = MAX_COOR - dx;
			if (dy > MAX_COOR / 2) dy = MAX_COOR - dy;

			int distance = dx + dy;

			// 3. Ïðîâåðêà äèñòàíöèè
			if (distance <= r) {
				//printf("Me %d with the pos (%d, %d) found target %d at the pos (%d, %d) to %d\n",this->get_rang(), this->get_x(), this->get_y(), target->get_rang(), target->get_x(), target->get_y(), i);
				return target; // Íàøëè öåëü — ñðàçó âîçâðàùàåì å¸
			}
			// Åñëè äàëåêî — ïðîñòî èäåì äàëüøå ïî öèêëó (continue íå îáÿçàòåëåí, ò.ê. êîíåö áëîêà)
		}

	}

	return nullptr;
}

bool MapObj::chase_targ(MapObj* target, Map* m) {
	if (!can_be_moved() || target == nullptr || m == nullptr) {
		return false; //êàïóñòà íèêîãî íå ëîâèò
	}

	int dx = target->get_x() - x;
	int dy = target->get_y() - y;

	if (dx > MAX_COOR / 2) dx -= MAX_COOR; //îòðèö çàíà÷åíèå dx äâèæåíèå âëåâî, åñëè êîðî÷å ñëåâà - çàéäåì ñëåâà
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR;  // åñëè ñïðàâà áëèæå - ïîéäåì ñïðàâà

	if (dy > MAX_COOR / 2) dy -= MAX_COOR; //îòðèö çàíà÷åíèå dx äâèæåíèå âíèç, åñëè êîðî÷å ñëåâà - çàéäåì ñíèçó
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // åñëè ñâåðõó áëèæå - ïîéäåì ñâåðõó

	// Äâèæåíèå òîëüêî íà îäèí øàã ê öåëè
	if (dx != 0) dx = (dx > 0) ? 1 : -1;
	if (dy != 0) dy = (dy > 0) ? 1 : -1;

	return move_on(dx, dy, m, true);  //äâèãàåìÿ ïðîïóñêàÿ ôàçó ïðåñëåäîâàíèÿ
}


bool MapObj::eat(Map* m) {
	if (m == nullptr) return false;
	MapObj* target = find_targ(1, m);
	if (!can_be_moved() || target == nullptr) {
		return false; //êàïóñòà íèêîãî íå åñò
	}
	//printf("the target %d  at position (%d, %d), was killed\n", target->get_rang(), target->get_x(), target->get_y());
	m->kill(target);
	stamina += PLUS_S;
	return true;
}

bool MapObj::move_on(int dx, int dy, Map* m, bool skip_chase_logic = true) {
	if (m == nullptr) return false;
	if (!can_be_moved()) return false;

	// Îãðàíè÷èâàåì äàëüíîñòü õîäà
	if (dx > MAX_SHIFT) dx = MAX_SHIFT;
	else if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;

	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	else if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;

	// --- ÈÑÏÐÀÂËÅÍÈÅ 1: Ëîãèêà ïðåñëåäîâàíèÿ ---
	// Â chase_targ âû âûçûâàåòå move_on ñ false, à òóò ïðîâåðÿåòå !nskip. 
	// Ýòî âûçûâàëî áû áåñêîíå÷íûé öèêë.
	// Çäåñü ìû ïðîâåðÿåì: åñëè ìû ÍÅ â ðåæèìå âûïîëíåíèÿ ïîãîíè (skip_chase_logic == false), 
	// òî èùåì öåëü.
	if (!skip_chase_logic && find_targ(0, m) != nullptr) {
		return chase_targ(find_targ(0, m), m);
	}

	// Ðàññ÷èòûâàåì íîâûå êîîðäèíàòû
	int new_x = x + dx;
	int new_y = y + dy;

	// Ðàçìåð êàðòû (åñëè êîîðäèíàòû 0..15, òî ðàçìåð 16)
	int map_size = MAX_COOR + 1;

	// --- ÈÑÏÐÀÂËÅÍÈÅ 2: Ïðàâèëüíûé Òîð (çàöèêëèâàíèå) ---
	// Âàøà ñòàðàÿ ôîðìóëà ñäâèãàëà êëåòêè íåïðàâèëüíî ïðè ïåðåõîäå ÷åðåç 0
	if (new_x < 0) new_x += map_size;
	else if (new_x > MAX_COOR) new_x -= map_size;

	if (new_y < 0) new_y += map_size;
	else if (new_y > MAX_COOR) new_y -= map_size;

	// --- ÈÑÏÐÀÂËÅÍÈÅ 3 (ÃËÀÂÍÎÅ): Ðàñ÷åò ñòàìèíû ---
	// Ñ÷èòàåì ðàñõîä ïî ÐÅÀËÜÍÎ ïðîéäåííîìó ïóòè (dx, dy), à íå ïî ñêà÷êó êîîðäèíàò
	int cost = (abs(dx) + abs(dy)) * EFFORT;
	stamina -= cost;

	if (!is_alive()) {
		m->kill(this); // Óìåð îò óñòàëîñòè
		return false;
	}

	x = new_x;
	y = new_y;
	return true;
}


//ïåðåâîä ñ Ñè

extern "C" {
	int get_s(MapObj* obj) {
		return obj->get_s();
	}
	int give_s(MapObj* obj, int ds) {
		if (ds + obj->get_s() > MAX_STAMINA || ds + obj->get_s() < 0) {
			return 1; //îøèáêà
		}
		else {
			obj->give_s(ds);
			return 0; //óñïåõ 
		}
	}
	int move_on(MapObj* obj, int dx, int dy, Map* m, int mode) {
		// mode == 1 -> ËÎÂÈÒÜ
		// mode == 0 -> ÏÐÎÑÒÎ ÈÄÒÈ (íå ëîâèòü)

		if (obj == nullptr || m == nullptr) return 1; //îøèáêà 

		if (mode == 1) {
			// Ìû õîòèì ËÎÂÈÒÜ. Çíà÷èò, "ïðîïóñê ïîãîíè" äîëæåí áûòü false.
			obj->move_on(dx, dy, m, false);
		}
		else {
			// Ìû õîòèì ïðîñòî èäòè (ÍÅ ËÎÂÈÒÜ). Çíà÷èò, "ïðîïóñê ïîãîíè" äîëæåí áûòü true.
			obj->move_on(dx, dy, m, true);
		}

		return 0;
	}
}



