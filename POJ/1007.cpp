#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define N 51
#define M 101

int POJ1007() {
	char str[M][N];
	int inv[M][2];
	int len, row, i, j, k, t;
	scanf("%d %d", &len, &row);
	i = 0;
	while (i < row) {
		scanf("%s", str[i++]);
	}
	for (k = 0; k < row; k++) {
		inv[k][0] = 0;
		inv[k][1] = k;
		for (i = 0; i < len - 1; i++) {
			for (j = i + 1; j < len; j++) {
				if (str[k][i] > str[k][j]) {
					inv[k][0]++;
				}
			}
		}
	}
	// ∂‘ƒÊ–Ú ˝√∞≈›≈≈–Ú
	for (i = 0; i < row - 1; i++) {
		for (j = i + 1; j < row; j++) {
			if (inv[j][0] < inv[i][0]) {
				t = inv[i][0];
				inv[i][0] = inv[j][0];
				inv[j][0] = t;
				t = inv[i][1];
				inv[i][1] = inv[j][1];
				inv[j][1] = t;
			}
		}
	}
	for (k = 0; k < row; k++) {
		printf("%s\n", str[inv[k][1]]);
	}
	return 0;
}