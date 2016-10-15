#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int POJ1004() {
	int n = 12;
	double f, t;
	f = t = 0.00f;
	while (n--) {
		scanf("%lf", &f);
		t += f;
	}
	printf("$%.02lf\n", t/12);
	return 0;
}