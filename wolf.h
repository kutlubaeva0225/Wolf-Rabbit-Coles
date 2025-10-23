#include <cstdlib>
#include <ctime>  
#include <cstdio>
#include "mapobj.h"

#ifndef WOLF_H_
#define WOLF_H_

#define CRIT_AGG 0.4 // ����������� �������������� 
class Wolf: public MapObj {
private:
	  double agger; //agger -- ����������� c����� ����� � ���� ������� 
public: 
	Wolf(int x, int y, int start_s, int rang, double agger); //����������� �����
	double get_ag() const; //�������� �������������
	void update_agg(); //�������� �������������
	bool wanna_eat(); 
};

Wolf::Wolf(int x, int y, int start_s, int rang, double s_agger ) : MapObj(x, y, start_s, 2), agger(s_agger) {
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

bool wanna_eat() { //���� ������, ���� ���������� �������� 
	if (agger > CRIT_AGG ) {
		 return eat();
	}
	else return false;
}

#endif
