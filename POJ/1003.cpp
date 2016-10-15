#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int POJ1003() {
	int n;
	double f, r;
	while (scanf("%lf", &f)){
		if (f == 0.00f)break;
		n = 2;
		r = 0.0f;
		while (r < f) {
			r = r + 1.0f / n;
			n = n + 1;
		}
		printf("%d card(s)\n", n - 2);
	}
	return 0;
}