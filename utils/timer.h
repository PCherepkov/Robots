/* Property of Cherepkov Petr
 * FILE: 'timer.h'
 * LAST UPDATE: 07.10.2021
 */

#include "../def.h"

/* timer handling functions */

#pragma once

class timer
{
public:
	dbl
		time, delta_time, start_time,
		fps;
	bool is_pause;

	timer() {
		time = start_time = (dbl)clock() / CLOCKS_PER_SEC;
		delta_time = 0;
	}

	~timer() {
	}

	void UpdateTimer(void) {
		dbl new_time = (dbl)clock() / CLOCKS_PER_SEC;
		delta_time = new_time - time;
		time = new_time;
		fps = 1 / delta_time;
	}
};


 /* END OF 'timer.h' FILE */
