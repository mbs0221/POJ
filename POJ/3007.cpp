/**
* 很久之前看过编程珠玑，了解到字符串转置操作的特性，现在算是派上了用场
* 我们可以将一个字符串看做两个连接的部分A和B，即AB，字符串的翻转操作T(x)就有如下一些特点
* T(T(A)) = A
* T(AB) = T(B)T(A)
* 确实是和矩阵的转置和乘法运算类似。
* 靠这两个特性，我们可以分别从不同的位置对字符串分隔，并对这两部分进行一系列的转置操作，
* 就可以获得字符串的不同组合，在此使用就地转置的方式，理论上一共可以获得八种组合。
* 最后因为要考虑不同的字符串的个数，为了提高速度，使用自定义的HashMap来统计字符串个数
* 最后整个算法的核心就是这个就地转置操作void reverse(char *str, int start, int end)
* 这样我们就可以不需要拆分连接字符串，也不需要占用额外的内存空间来获取字符串AB的不同组合
* 最后,由于在进行操作开始的时候，需要清空map，如果彻底清空map，则会导致超时，
* 如果不清空map，只是简单的对map数组中的指针置空，又会浪费大量不再需要的内存空间，
* 为了缩短运行时间，还是不回收这些空间了。
**/

#define __EDG__ 1 // 由于所用VS2015出现问题，需要加上该宏才能顺利编译

#include <stdio.h>
#include <string.h>

struct list {
	char str[73];
	list *next;
}*map[256];

int result;

// 插入元素
void insert(char *str) {
	int n = strlen(str);
	int hash = 0;
	for (int i = 0; i < n; i++) {
		hash += str[i] * n;
	}
	hash %= 256;
	list *p = map[hash];
	if (p) {
		bool find = false;
		while (p->next) {
			if (!strcmp(p->str, str)) {
				// 已经存在，无需添加
				return;
			}
			p = p->next;
		}
		// 最后一个
		if (!strcmp(p->str, str)) {
			// 已经存在，无需添加
			return;
		}
		// 拉链法解决冲突
		result++;
		p->next = new list;
		p->next->next = NULL;
		strcpy_s(p->next->str, str);
	}
	else {
		// 无冲突直接添加
		result++;
		map[hash] = new list;
		map[hash]->next = NULL;
		strcpy_s(map[hash]->str, str);
	}
}

// 清空map
void clear() {
	list *t, *p;
	for (int i = 0; i < 256; i++) {
		// 如果添加如下代码来清空map中的所有元素，则会导致提交OJ超时
		// 在此可以添加代码，减小内存开销，提交OJ时可去掉，以减小时间开销
		p = map[i];
		while (p){
			t = p;
			p = p->next;
			delete t;
		}
		// 必须置空初始化
		map[i] = NULL;
	}
}

// 对str字符串从下标start到end就地翻转
void reverse(char *str, int start, int end) {
	while (start < end) {
		char c = str[end];
		str[end] = str[start];
		str[start] = c;
		start++, end--;
	}
}

// Organize Your Train part II 
int	POJ3007() {
	int n, mid, length;
	char c, str[73];
	memset(str, '\0', 73);
	scanf_s("%d\n", &n);
	while (n--) {
		gets_s(str);
		result = 0;
		length = strlen(str);
		clear();
		// 根据字符串翻转的规律，使用如下方法，可以就地生成字符串AB的不同翻转拼接组合
		// 而不需要使用额外的存储空间，最后insert到map中以记录该字符串
		// 其中T(x)为翻转x字符串，A为字符串str前面一部分，B为字符串str后面一部分
		// 其中mid为开始分隔的位置
		// 得到AB
		insert(str);
		for (int i = 1; i < length; i++) {
			// Part I
			mid = i;
			// 得到AT(B)
			reverse(str, mid, length - 1);
			insert(str);
			// 得到T(A)T(B)
			reverse(str, 0, mid - 1);
			insert(str);
			// 得到T(A)B
			reverse(str, mid, length - 1);
			insert(str);
			// Part II
			mid = length - i;
			// 得到T(B)A
			reverse(str, 0, length - 1);
			insert(str);
			// 得到BA
			reverse(str, 0, mid - 1);
			insert(str);
			// 得到BT(A)
			reverse(str, mid, length - 1);
			insert(str);
			// 得到T(B)T(A)
			reverse(str, 0, mid - 1);
			insert(str);
			// Part III
			reverse(str, 0, length - 1);
		}
		printf("%d\n", result);
	}
	getchar();
	return 0;
}