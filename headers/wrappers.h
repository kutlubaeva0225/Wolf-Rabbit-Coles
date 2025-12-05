#ifndef MAP_WRAPPERS_H
#define MAP_WRAPPERS_H

class Map;
class MapObj;

extern "C" {
    Map* create_map(int w, int r, int c);
    void del_map(Map* m);
    void m_print(Map* m);
    int make_step(Map* m);
    int if_game_over(Map* m);
	int get_s(MapObj* obj);
	int give_s(MapObj* obj, int ds);
	int move_on(MapObj* obj, int dx, int dy, Map* m, int mode);
}


#endif
