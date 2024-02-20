#include <stdio.h>

#include "../src/stats.h"

int add(int a, int b) {
	return a + b;
}

int mul(int a, int b) {
	return a * b;
}

double div(double a, double b) {
	return a / b;
}

int main(int argc, char *argv[]) {

	int r1, r2, r3;
	double r4, r5;

#ifdef ENABLE_RUNTIME_STATS
	timer_start();
#endif

	printf("argc = %d, argv[1] = %s\n", argc, argv[1]);

	r1 = add(10, 7);

	r2 = add(9, 4);

	r3 = mul(r1, r2);

	printf("r3 result = %d\n", r3);

	r4 = div(10.0, 3.0);

	printf("r4 result = %lf\n", r4);

	r5 = div(2.2, 2.0);

	printf("r5 result = %lf\n", r5);

#ifdef ENABLE_RUNTIME_STATS
	timer_end();
	runtime_save();
#endif

}