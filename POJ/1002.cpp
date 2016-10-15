#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Trie树节点类
struct node {
	int times;
	bool valid;
	node *next[10];
	node() {
		int i;
		times = 0;
		valid = false;
		for (i = 0; i < 10; i++) {
			next[i] = NULL;
		}
	}
};

// 添加电话号码
void insert(node *root, char *str) {
	char c = '0';
	char *pc = str;
	node *pn = root;
	while (*pc != '\0') {
		switch(*pc) {
		case 'A':
		case 'B':
		case 'C':c = '2'; break;
		case 'D':
		case 'E':
		case 'F':c = '3'; break;
		case 'G':
		case 'H':
		case 'I':c = '4'; break;
		case 'J':
		case 'K':
		case 'L':c = '5'; break;
		case 'M':
		case 'N':
		case 'O':c = '6'; break;
		case 'P':
		case 'R':
		case 'S':c = '7'; break;
		case 'T':
		case 'U':
		case 'V':c = '8'; break;
		case 'W':
		case 'X':
		case 'Y':c = '9'; break;
		case 'Q':
		case 'Z':
		case '-':pc++; continue;
		default:c = *pc; break;
		}
		if (pn->next[c - '0']) {
			pn = pn->next[c - '0'];
		}else {
			pn->next[c - '0'] = new node();
			pn = pn->next[c - '0'];
		}
		pc++;
	}
	pn->times++;
	pn->valid = true;
}

char str[10];
char top = 0;
bool dup = false;

// 格式化输出出现次数大于1的电话号码
void print(node *root) {
	int i;
	if (root->valid) {
		str[top] = '\0';
		if (root->times > 1) {
			dup = true;
			printf("%s %d\n", str, root->times);
		}
		return;
	}
	for (i = 0; i < 10; i++) {
		if (root->next[i]) {
			if (top == 3)str[top++] = '-';
			str[top++] = i + '0';
			print(root->next[i]);
			str[--top] = '\0';
			if (top == 4)str[--top] = '\0';
		}
	}
}

// 487-3279
int POJ1002() {
	int n;
	char str[256];
	node *root = new node();
	scanf("%d", &n);
	while (n--) {
		scanf("%s", str);
		insert(root, str);
	}
	print(root);
	if (!dup)
		printf("No duplicates.\n");
	return 0;
}