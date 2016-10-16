#define _CRT_SECURE_NO_WARNINGS
#define __EDG__ 1

#include <stdio.h>
#include <string.h>

char *months[19] = {
	"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", 
	"zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"
};

char *names[20] = {
	"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", 
	"chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"
};

struct list {
	int value;
	char name[8];
	list *next;
};

class map{
	list *data[256];
public:
	map() {
		for (int i = 0; i < 256; i++) {
			data[i] = NULL;
		}
	}
	~map() {
		list *t, *p;
		for (int i = 0; i < 256; i++) {
			p = data[i];
			while (p) {
				t = p;
				p = p->next;
				delete t;
			}
			data[i] = NULL;
		}
	}
	void insert(char *name, int value) {
		int i, n;
		int hash = 0;
		n = strlen(name);
		for (i = 0; i < n; i++) {
			hash += name[i];
		}
		hash %= 256;
		list *p = data[hash];
		if (p) {
			while (p->next) {
				if (!strcmp(p->name, name)) {
					return;
				}
				p = p->next;
			}
			if (!strcmp(p->name, name)) {
				return;
			}
			p->next = new list;
			p->next->next = NULL;
			p->next->value = value;
			strcpy_s(p->next->name, name);
		}else {
			data[hash] = new list;
			data[hash]->next = NULL;
			data[hash]->value = value;
			strcpy_s(data[hash]->name, name);
		}
	}
	list *operator [](char *name) {
		int  i, n;
		n = strlen(name);
		int hash = 0;
		for (i = 0; i < n; i++) {
			hash += name[i];
		}
		hash %= 256;
		list *p = data[hash];
		if (p) {
			while (p) {
				if (!strcmp(p->name, name)) {
					return p;
				}
				p = p->next;
			}
		}
		return NULL;
	}
};

int main() {
	map m;
	int i, n, day, year, days;
	char *month = new char[32];
	char **results;
	for (i = 0; i < 19; i++) {
		m.insert(months[i], i);
	}
	// ÊäÈëHaab calendar
	scanf("%d", &n);
	results = new char*[n];
	i = 0;
	while (i < n) {
		scanf("%d. %s %d", &day, month, &year);
		days = 365 * year + m[month]->value * 20 + day;
		results[i] = new char[32];
		sprintf(results[i], "%d %s %d", (days % 13) + 1, names[days % 20], days / 260);
		i++;
	}
	// Êä³öTzolkin calendar
	printf("%d\n", n);
	i = 0;
	while (i < n) {
		printf("%s\n", results[i]);
		i++;
	}
	return 0;
}