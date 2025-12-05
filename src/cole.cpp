#include <cstdio>
#include <cstdlib>
#include "mapobj.h"
#include "cole.h"


#define COLE_P_S 1

Cole::Cole(int x, int y, int start_s, int rang) : MapObj(x, y, 1, 0) {}

bool Cole::can_be_moved() const {
	return false;
};
bool Cole::give_s(int ds) {
	stamina += COLE_P_S; //ïîäêàðìëèâàåì çà COLE_P_S 
	return true;
};
