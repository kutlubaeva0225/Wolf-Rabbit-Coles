#include <cstdlib>
#include <ctime>  
#include <cstdio>
#include "mapobj.h"
#include "map.h"

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
	bool wanna_eat(Map* map);
};

#endif
