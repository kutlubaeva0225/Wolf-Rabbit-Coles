#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>




#ifndef MAPOBJ_H_
#define MAPOBJ_H_

#define MAX_N_OBJ 10
#define MAX_STAMINA 20
#define PLUS_S 5 //сколько цель сил даст объекту
#define EFFORT 1 //затрата сил на перемещение на единицу длинны
#define MAX_SHIFT 3 //максимальное перемещение за один шаг моделирования
#define R_VIEW 4 //радиус обзора 
#define R_DRAP 1 //радиус захвата пищи
#define MAX_COOR 15 //размер карты 
#define START_S MAX_STAMINA / 2

class Map;

class MapObj {
private: 
	int x; int y; 
protected:
	int stamina;  int rang; //rang относится к типу объекта: B > З > К. Если r1 = r2 + 1, то 1 догоняет 2 r_K = 0, у капусты положим их нулем r = 0 и беск выносливость 
public:
	MapObj(int x, int y, int stamina, int rang);
	virtual bool can_be_moved() const; //перегрузим в капусте на false
	int get_x() const;
	int get_y() const;
	int get_rang() const;
	int get_s() const;
	bool move_on(int dx, int dy, Map* m, bool nskip_chase); //для всех одна, если объкт движется, с учетом погони за более низкоранговыми, если не должны прокускать фазу погони 
	MapObj* find_targ(int i, Map* m); //// если i = 0, то в зоне видимости, если i = 1, то ищем зайца в зоне захвата. Для капусты ничего не происходит 
	bool chase_targ(MapObj* target, Map* m); //для капусты будет просто завершаться 
	bool eat(Map* m);// капуста не сможет съесть 
	bool is_alive() const;
	virtual bool give_s(int ds); // подкормить волка, зайку, в капусте перезагрузим и будем каждый раз давать одно и то же значение 
};
#endif


