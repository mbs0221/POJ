#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 400

char w[N];
int nw, fw;

// 翻转字符串
void reverse(char *str) {
	int start, end;
	start = 0, end = strlen(str) - 1;
	while (start < end) {
		char c = str[end];
		str[end] = str[start];
		str[start] = c;
		start++, end--;
	}
}

// 字符串转浮点数，nx为浮点数位数，fx为整数部分的位数
void c_atoi(char *x, int *nx, int *fx) {
	char *p = x, *q = x;
	*fx = strchr(x, '.') - x;
	reverse(x);
	while (*p != '\0') {
		if (*p == '.')p++;
		*q++ = *p++ - '0';
	}
	*nx = q - x;
}

// 浮点数转字符串，nx为浮点数位数，fx为整数部分的位数
void c_itoa(char *x, int nx, int fx) {
	char *p = x + nx;
	char *q = x + nx + 1;
	// 转浮点数字符串
	while (p != x) {
		*q = *p + '0';
		q--, p--;
		if (q - x == nx - fx) {
			*q-- = '.';
		}
	}
	*q = *p + '0';
	// 翻转数字串
	reverse(x);
	// 去掉开始的'0'
	while (*q == '0')q++;
	while (*p++ = *q++);
	// 去掉结尾的'0'
	q = x + strlen(x) - 1;
	while (*q == '0')q--;
	// 如果是整数，不输出'.'
	if (*q == '.')*q = '\0';
	else *(++q) = '\0';
}

// 浮点数乘法运算
void mul(char *x, char *y, char *z, int nx, int ny, int *nz, int fx, int fy, int *fz) {
	int i, j;
	for (j = 0; j < ny; j++) {
		for (i = 0; i < nx; i++) {
			z[i + j] += x[i] * y[j];
			z[i + j + 1] += z[i + j] / 10;
			z[i + j] = z[i + j] % 10;
		}
	}
	*fz = fx + fy;
	*nz = nx + ny;
}

// 高精度浮点数幂运算
void power(char *x, char *y, int ep, int nx, int *ny, int fx, int *fy) {
	y[0] = 0, y[1] = 1;
	*ny = 2, *fy = 1;
	while (ep--) {
		mul(x, y, w, nx, *ny, &nw, fx, *fy, &fw);
		memcpy(y, w, nw);
		memset(w, 0, nw);
		*ny = nw, *fy = fw;
	}
}

// Exponentiation
int POJ1001() {
	char x[N], y[N];
	int ep, nx, fx, ny, fy;
	double f;
	while (scanf_s("%6lf %2d", &f, &ep) == 2) {
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(w, 0, sizeof(w));
		sprintf_s(x, "%lf", f);
		c_atoi(x, &nx, &fx);
		power(x, y, ep, nx, &ny, fx, &fy);
		c_itoa(y, ny, fy);
		printf("%s\n", y);
	}
	return 0;
}