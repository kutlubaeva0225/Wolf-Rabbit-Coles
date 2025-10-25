#include <cstdlib>
#include <ctime>  
#include <cstdio>
#include "mapobj.h"
#include "wolf.h"

Wolf::Wolf(int x, int y, int start_s, int rang, double s_agger) : MapObj(x, y, start_s, 2), agger(s_agger) {
	if (agger < 0) agger = 0;
	if (agger > 1) agger = 1;
}

void Wolf::update_agg() {
	double new_agg = (double)rand() / RAND_MAX;
	agger = new_agg;
}
double Wolf::get_ag() const {
	return agger;
}

bool Wolf::wanna_eat(Map* map) { //едим только, если достаточно голодные 
	if (agger > CRIT_AGG) {
		return eat(map);
	}
	else return false;
}