#include "BBT.h"


int cnt, T, root;
struct treap tree[MAXN];

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}

void pushup(int x) {
	tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + 1;
}

void rotate_r(int *x) {
	int ll = tree[*x].l;
	tree[*x].l = tree[ll].r;
	tree[ll].r = *x;
	tree[ll].size = tree[*x].size;
	pushup(*x);
	*x = ll;
}

void rotate_l(int *x) {
	int rr = tree[*x].r;
	tree[*x].r = tree[rr].l;
	tree[rr].l = *x;
	tree[rr].size = tree[*x].size;
	pushup(*x);
	*x = rr;
}

void insert(int *x, int goal) {
	if (*x == 0) {
		*x = ++cnt;
		tree[*x].size = 1;
		tree[*x].data = goal;
		tree[*x].val = (rand() * rand()) % 20040610;
		return;
	}
	tree[*x].size++;
	if (goal >= tree[*x].data) {
		insert(&tree[*x].r, goal);
	} else {
		insert(&tree[*x].l, goal);
	}
	if (tree[*x].l != 0 && tree[*x].val > tree[tree[*x].l].val) {
		rotate_r(x);
	}
	if (tree[*x].r != 0 && tree[*x].val > tree[tree[*x].r].val) {
		rotate_l(x);
	}
	pushup(*x);
}

void del(int *x, int goal) {
	tree[*x].size--;
	if (tree[*x].data == goal) {
		if (tree[*x].l == 0 && tree[*x].r == 0) {
			*x = 0;
			return;
		} else if (tree[*x].l == 0 || tree[*x].r == 0) {
			*x = tree[*x].l + tree[*x].r;
			return;
		}
		if (tree[tree[*x].l].val < tree[tree[*x].r].val) {
			rotate_r(x);
			del(&tree[*x].r, goal);
			return;
		} else {
			rotate_l(x);
			del(&tree[*x].l, goal);
			return;
		}
	}
	if (tree[*x].data >= goal) {
		del(&tree[*x].l, goal);
	} else {
		del(&tree[*x].r, goal);
	}
	pushup(*x);
}

int kth(int x, int goal) {
	if (x == 0) {
		return 0;
	}
	if (goal <= tree[x].data) {
		return kth(tree[x].l, goal);
	} else {
		return tree[tree[x].l].size + 1 + kth(tree[x].r, goal);
	}
}

int query(int x, int k) {
	if (k == tree[tree[x].l].size + 1) {
		return tree[x].data;
	} else if (k < tree[tree[x].l].size + 1) {
		return query(tree[x].l, k);
	} else {
		return query(tree[x].r, k - tree[tree[x].l].size - 1);
	}
}

int pre(int x, int goal) {
	if (x == 0) {
		return 0;
	}
	if (tree[x].data >= goal) {
		return pre(tree[x].l, goal);
	} else {
		int rnum = pre(tree[x].r, goal);
		if (rnum == 0) {
			return tree[x].data;
		} else {
			return rnum;
		}
	}
}

int succ(int x, int goal) {
	if (x == 0) {
		return 0;
	}
	if (tree[x].data <= goal) {
		return succ(tree[x].r, goal);
	} else {
		int lnum = succ(tree[x].l, goal);
		if (lnum == 0) {
			return tree[x].data;
		} else {
			return lnum;
		}
	}
}

void print(int x,int dep){
	if(tree[x].l!=0)print(tree[x].l,dep+1);
	for(int i=1;i<=dep;i++)printf("-");
	printf("%d\n",tree[x].data);
	if(tree[x].r!=0)print(tree[x].r,dep+1);
}

int main() {
	memset(tree, 0, sizeof(tree));
	srand(71806291);
	while(1) {
		//打印输入提示
		printf("Please input the operation type and the number:\n");
		printf("1: insert\n");
		printf("2: delete\n");
		printf("3: find the k-th number\n");
		printf("4: find the rank of the number\n");
		printf("5: find the predecessor\n");
		printf("6: find the successor\n");
		printf("-1: exit\n");
		int opt = read(), xx = read();
		switch (opt) {
			case 1:
				insert(&root, xx);
				break;
			case 2:
				del(&root, xx);
				break;
			case 3:
				printf("%d\n", kth(root, xx) + 1);
				break;
			case 4:
				printf("%d\n", query(root, xx));
				break;
			case 5:
				printf("%d\n", pre(root, xx));
				break;
			case 6:
				printf("%d\n", succ(root, xx));
				break;
			case -1:
				return 0;
			default:
				printf("Invalid operation type!\n");
				break;
		}
		printf("current tree is :\n");
		print(root,0);
	}
	return 0;
}
/*
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598
*/