#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 400

char w[N];
int nw, fw;

// ��ת�ַ���
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

// �ַ���ת��������nxΪ������λ����fxΪ�������ֵ�λ��
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

// ������ת�ַ�����nxΪ������λ����fxΪ�������ֵ�λ��
void c_itoa(char *x, int nx, int fx) {
	char *p = x + nx;
	char *q = x + nx + 1;
	// ת�������ַ���
	while (p != x) {
		*q = *p + '0';
		q--, p--;
		if (q - x == nx - fx) {
			*q-- = '.';
		}
	}
	*q = *p + '0';
	// ��ת���ִ�
	reverse(x);
	// ȥ����ʼ��'0'
	while (*q == '0')q++;
	while (*p++ = *q++);
	// ȥ����β��'0'
	q = x + strlen(x) - 1;
	while (*q == '0')q--;
	// ����������������'.'
	if (*q == '.')*q = '\0';
	else *(++q) = '\0';
}

// �������˷�����
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

// �߾��ȸ�����������
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