#include <cstdlib>
#include <ctime>  
#include <cstdio>
#include "mapobj.h"
#include "map.h"

#ifndef WOLF_H_
#define WOLF_H_

#define CRIT_AGG 0.4 // êðèòè÷åñêàÿ àããðåññèâíîñòü 
class Wolf: public MapObj {
private:
	  double agger; //agger -- ââåðîÿòîñòü cüåñòü çàéöà â ïîëå çàõâàòà 
public: 
	Wolf(int x, int y, int start_s, int rang, double agger); //êîíñòðóêòîð âîëêà
	double get_ag() const; //ïîëó÷èòü àãðåññèâíîñòü
	void update_agg(); //îáíîâèòü àããðåñèâíîñòü
	bool wanna_eat(Map* map);
};

#endif
