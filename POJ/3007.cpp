/**
* �ܾ�֮ǰ����������ᣬ�˽⵽�ַ���ת�ò��������ԣ����������������ó�
* ���ǿ��Խ�һ���ַ��������������ӵĲ���A��B����AB���ַ����ķ�ת����T(x)��������һЩ�ص�
* T(T(A)) = A
* T(AB) = T(B)T(A)
* ȷʵ�Ǻ;����ת�úͳ˷��������ơ�
* �����������ԣ����ǿ��Էֱ�Ӳ�ͬ��λ�ö��ַ����ָ��������������ֽ���һϵ�е�ת�ò�����
* �Ϳ��Ի���ַ����Ĳ�ͬ��ϣ��ڴ�ʹ�þ͵�ת�õķ�ʽ��������һ�����Ի�ð�����ϡ�
* �����ΪҪ���ǲ�ͬ���ַ����ĸ�����Ϊ������ٶȣ�ʹ���Զ����HashMap��ͳ���ַ�������
* ��������㷨�ĺ��ľ�������͵�ת�ò���void reverse(char *str, int start, int end)
* �������ǾͿ��Բ���Ҫ��������ַ�����Ҳ����Ҫռ�ö�����ڴ�ռ�����ȡ�ַ���AB�Ĳ�ͬ���
* ���,�����ڽ��в�����ʼ��ʱ����Ҫ���map������������map����ᵼ�³�ʱ��
* ��������map��ֻ�Ǽ򵥵Ķ�map�����е�ָ���ÿգ��ֻ��˷Ѵ���������Ҫ���ڴ�ռ䣬
* Ϊ����������ʱ�䣬���ǲ�������Щ�ռ��ˡ�
**/

#define __EDG__ 1 // ��������VS2015�������⣬��Ҫ���ϸú����˳������

#include <stdio.h>
#include <string.h>

struct list {
	char str[73];
	list *next;
}*map[256];

int result;

// ����Ԫ��
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
				// �Ѿ����ڣ��������
				return;
			}
			p = p->next;
		}
		// ���һ��
		if (!strcmp(p->str, str)) {
			// �Ѿ����ڣ��������
			return;
		}
		// �����������ͻ
		result++;
		p->next = new list;
		p->next->next = NULL;
		strcpy_s(p->next->str, str);
	}
	else {
		// �޳�ͻֱ�����
		result++;
		map[hash] = new list;
		map[hash]->next = NULL;
		strcpy_s(map[hash]->str, str);
	}
}

// ���map
void clear() {
	list *t, *p;
	for (int i = 0; i < 256; i++) {
		// ���������´��������map�е�����Ԫ�أ���ᵼ���ύOJ��ʱ
		// �ڴ˿�����Ӵ��룬��С�ڴ濪�����ύOJʱ��ȥ�����Լ�Сʱ�俪��
		p = map[i];
		while (p){
			t = p;
			p = p->next;
			delete t;
		}
		// �����ÿճ�ʼ��
		map[i] = NULL;
	}
}

// ��str�ַ������±�start��end�͵ط�ת
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
		// �����ַ�����ת�Ĺ��ɣ�ʹ�����·��������Ծ͵������ַ���AB�Ĳ�ͬ��תƴ�����
		// ������Ҫʹ�ö���Ĵ洢�ռ䣬���insert��map���Լ�¼���ַ���
		// ����T(x)Ϊ��תx�ַ�����AΪ�ַ���strǰ��һ���֣�BΪ�ַ���str����һ����
		// ����midΪ��ʼ�ָ���λ��
		// �õ�AB
		insert(str);
		for (int i = 1; i < length; i++) {
			// Part I
			mid = i;
			// �õ�AT(B)
			reverse(str, mid, length - 1);
			insert(str);
			// �õ�T(A)T(B)
			reverse(str, 0, mid - 1);
			insert(str);
			// �õ�T(A)B
			reverse(str, mid, length - 1);
			insert(str);
			// Part II
			mid = length - i;
			// �õ�T(B)A
			reverse(str, 0, length - 1);
			insert(str);
			// �õ�BA
			reverse(str, 0, mid - 1);
			insert(str);
			// �õ�BT(A)
			reverse(str, mid, length - 1);
			insert(str);
			// �õ�T(B)T(A)
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