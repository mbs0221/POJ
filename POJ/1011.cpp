#define _CRT_SECURE_NO_WARNINGS
#define __EDG__ 1

// printf("search:%4d\t%4d\t%4d\n", nlength, count, current);

#include <stdio.h>
#include <string.h>

int n, max, sum, num, length, sticks[64], visited[64];
int flag;

void DFS(int nlength, int count, int current) {
	int i;
	if (count == num) {
		flag = 1;
		return;
	}
	if (flag) {
		return;
	}
	for (i = current; i < n; i++) {
		if (!visited[i] && nlength + sticks[i] <= length) {
			visited[i] = 1;
			if (nlength + sticks[i] == length) {
				// 凑够length长度
				DFS(0, count + 1, 0);
				visited[i] = 0;
				return;
			} else {
				// 没有凑够length长度
				DFS(nlength + sticks[i], count, i + 1);
				visited[i] = 0;
				if (nlength == 0 || flag) {
					return;
				}
			}
		}
	}
}

int POJ1011() {
	int i, j;
	while (scanf("%d", &n)) {
		if (n == 0)break;
		i = 0;
		sum = 0;
		while (i < n) {
			scanf("%d", &sticks[i]);
			sum += sticks[i];
			i++;
		}
		// 从小到大选择排序
		for (i = 0; i < n - 1; i++) {
			max = i;
			for (j = i + 1; j < n; j++) {
				if (sticks[j] > sticks[max]) {
					max = j;
				}
			}
			if (max != i) {
				int temp = sticks[i];
				sticks[i] = sticks[max];
				sticks[max] = temp;
			}
		}
		// 初始化visited
		for (i = 0; i < n; i++) {
			visited[i] = 0;
		}
		// DFS
		flag = 0;
		for (i = sticks[0]; i <= sum; i++) {
			if (sum % i == 0) {
				length = i;// 从最长棍子长度开始搜索
				num = sum / i;// 棍子总数为sum/i;
				DFS(0, 0, 0);
				if (flag) {
					break;
				}
			}
		}
		printf("%d\n", length);
	}
	return 0;
}