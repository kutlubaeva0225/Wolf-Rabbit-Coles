#include "test_w.h"

int main() {
	Wolf w1 = Wolf(-1, -1, -100, 2.0);
	if (t_create(&w1)) printf("Wolf created correctly\n");
	w1.move_on(100, -100);
	if (t_move_on(&w1)) printf("Wolf moved correctly\n");
	bool a = w1.give_s(100); //временная пременная, нуждые только для тестов
	if (t_give_stamina(&w1)) printf("You gave stamina correctly\n");
	w1.update_agg();
	if (t_update_agg(&w1)) printf("Agger was uppdated correctly");
	return 0;
}
