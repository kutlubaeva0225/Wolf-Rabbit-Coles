#include <cstdlib>
#include <ctime>  
#include <cstdio>
#include "mapobj.h"
#include "map.h"

#ifndef WOLF_H_
#define WOLF_H_

#define CRIT_AGG 0.4 // критическая аггрессивность 
class Wolf: public MapObj {
private:
	  double agger; //agger -- ввероятость cьесть зайца в поле захвата 
public: 
	Wolf(int x, int y, int start_s, int rang, double agger); //конструктор волка
	double get_ag() const; //получить агрессивность
	void update_agg(); //обновить аггресивность
	bool wanna_eat(Map* map);
};

#endif
