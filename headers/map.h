#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mapobj.h"
#include "wrappers.h "

#ifndef MAP_H_
#define MAP_H_
#define MAX_N_OBJ 20
#define MAX_STAMINA 20
#define PLUS_S 5 //ñêîëüêî öåëü ñèë äàñò îáúåêòó
#define EFFORT 1 //çàòðàòà ñèë íà ïåðåìåùåíèå íà åäèíèöó äëèííû
#define MAX_SHIFT 3 //ìàêñèìàëüíîå ïåðåìåùåíèå çà îäèí øàã ìîäåëèðîâàíèÿ
#define R_VIEW 4 //ðàäèóñ îáçîðà 
#define R_DRAP 1 //ðàäèóñ çàõâàòà ïèùè
#define MAX_COOR 15 //ðàçìåð êàðòû 
#define START_S MAX_STAMINA / 2

class Map {
private: 
	MapObj** objects; //äèí ìàññèâ äëÿ âñåõ óêàçàòåëåé îáúåêòîâ êàðòû
	int wolfs; //÷èñëî âîëêîâ 
	int rabbits; //÷èñëî çàéöåâ  
	int coles;//÷èñëî êàïóñò
	int obj_num;  // ÷èñëî îáúåêòîâ â ìàññèâå
	int curr_time; // òåêóùåå âðåìÿ 
public:
	Map(int w, int r, int c);
	void print() const; // âûâîä îòëàäî÷íîé òåêñòîâîé èíôîðìàöèè î êàðòå
	void kill(MapObj* target); //óáèòü öåëü
	void make_step(); //ñîâåðøèòü îäèí øàã èãðû 
	bool if_game_over(); // ïðîâåðÿåò îêîí÷åíà ëè èãðà, êîãäà âûæèë òîëüêî îäèí êëàññ 
	//Map* copy(Map* m); 
	std::vector<MapObj*> get_obj() const; //âîçâðàùàåò êîíòåéíåð îáúåêòîâ êàðòû
	~Map(); //ïèøåì äåñòðóêòîð, ÷òîáû íå áûëî óòå÷êè ïàìÿòè 
};

#endif
