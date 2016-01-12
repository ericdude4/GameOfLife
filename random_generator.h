#include <math.h>

/*
Author: Eric Froese
Student Number: 5029954
Description: This header uses the algorithm provided by Vlad Wojcik to return
a pseudo-random double between 0 and 1.
Course: COSC 4F00
Due Date: October 30, 2015
Assignment: 1
*/

class random_generator {
	private:
		int x;
		int y;
		int z;
	public:
		random_generator(int initX, int initY, int initZ):
		x(initX), y(initY), z(initZ) {}

		double nextDouble() {
			double decimals;
			double integer;
			x = 171*(x%177) - 2*(x/177);
			if (x < 0) {
				x += 30269;
			}
			y = 172*(y%176) - 35*(y/176);
			if (y < 0) {
				y += 30307;
			}
			z = 170*(z%178) - 63*(z/178);
			if (z < 0) {
				z += 30323;
			}
			decimals = x/30269.0 + y/30307.0+z/30323.0;
			modf(decimals, &integer);
			return decimals - integer;
		}
};