#include <cstdio>
#include <cstdlib>
#include "mapobj.h"
#include <climits>

#ifndef COLE_H_
#define COLE_H_ 

#define COLE_P_S 1

class Cole : public MapObj {
public:
	Cole(int x, int y, int start_s, int rang); //конструктор зайца
	bool can_be_moved() const;
	bool give_s(int ds);
};
Cole::Cole(int x, int y, int start_s, int rang) : MapObj(x, y, 1, 0) {}

bool Cole:can_be_moved() const {
	return false;
};
bool give_s(int ds) {
	stamina += COLE_P_S; //подкармливаем за COLE_P_S 
	return true;
};
#endif