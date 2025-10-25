#include <cstdio>
#include <cstdlib>
#include "mapobj.h"

#ifndef COLE_H_
#define COLE_H_ 

#define COLE_P_S 1

class Cole : public MapObj {
public:
	Cole(int x, int y, int start_s, int rang); //конструктор зайца
	bool can_be_moved() const;
	bool give_s(int ds);
};
#endif