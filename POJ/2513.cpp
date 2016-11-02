#define _CRT_SECURE_NO_WARNINGS
#define __EDG__ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 500
#define N 250000

struct list {
	char color[11];
	int value;
	list *next;
}*data[M];

int count = 0;

int insert(char *color) {
	int i, n;
	int hash = 0;
	list *p;
	n = strlen(color);
	for (i = 0; i < n; i++) {
		hash += color[i];
	}
	hash %= M;
	p = data[hash];
	if (p) {
		while (p->next) {
			if (!strcmp(p->color, color)) {
				return p->value;
			}
			p = p->next;
		}
		if (!strcmp(p->color, color)) {
			return p->value;
		}
		p->next = new list;
		p->next->value = count++;
		strcpy(p->next->color, color);
		return p->next->value;
	}
	else {
		data[hash] = new list;
		data[hash]->value = count++;
		data[hash]->next = NULL;
		strcpy(data[hash]->color, color);
		return data[hash]->value;
	}
}

int find(int *set, int x) {
	int i, j;
	int root;
	root = x;
	while (root != set[root])
		root = set[root];
	i = x;
	while (i != root) {
		j = set[i];
		set[i] = root;
		i = j;
	}
	return set[x];
}

int set[N];
int color[N];
int i, odd, u, v, root;

int main() {
	char a[11], b[11];
	for (i = 0; i < M; i++) {
		data[i] = NULL;
	}
	for (i = 0; i < N; i++) {
		set[i] = i;
		color[i] = 0;
	}
	while (scanf("%s %s", &a, &b)!=EOF) {
		u = insert(a);
		v = insert(b);
		++color[u];
		++color[v];
		u = find(set, u);
		v = find(set, v);
		if (u == v)continue;
		set[v] = u;
	}
	root = 0;
	odd = 0;
	for (i = 0; i < count; i++) {
		if (color[i] & 0x01)++odd;
		if (i == find(set, i))root++;
		if (odd > 2||root>1) {
				printf("Impossible\n");
				return 0;
		}
	}
	printf("Possible\n");
	return 0;
}