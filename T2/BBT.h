#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100010

struct treap {
	int val, data, l, r, size;
};

//根据BBT.c的代码，生成对应的函数声明

int read();
void pushup(int x);
void rotate_r(int *x);
void rotate_l(int *x);
void insert(int *x, int goal);
void del(int *x, int goal);
int kth(int x, int goal);
int query(int x, int k);
int pre(int x, int goal);
int succ(int x, int goal);

void print();