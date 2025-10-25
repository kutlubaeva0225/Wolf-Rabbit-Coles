#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "mapobj.h"

#ifndef RABBIT_H_
#define RABBIT_H_

class Rabbit : public MapObj {
public:
	Rabbit(int x, int y, int start_s, int rang); //конструктор зайца
};
#endif