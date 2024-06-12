#include <stdio.h>
#define ls tree[x].l
#define rs tree[x].r
using namespace std;
const int MAXN=1e5+10;
int cnt,T,root;
inline int read()
{
	int s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
struct treap{
	int val,data,l,r,size;
}tree[MAXN];

void pushup(int x)
{
	tree[x].size=tree[ls].size+tree[rs].size+1;
}

void rotate_r(int &x)
{
//	cout<<"r"<<x<<" "<<ls;
	int ll=ls; 
	tree[x].l=tree[ll].r;
	tree[ll].r=x;
	tree[ll].size=tree[x].size;
	pushup(x);
	x=ll; 
}

void rotate_l(int &x)
{
//	cout<<"l"<<x<<" "<<rs;
	int rr=rs;
	tree[x].r=tree[rr].l;
	tree[rr].l=x;
	tree[rr].size=tree[x].size;
	pushup(x);
	x=rr;
}

/*long long random(int x){
	return (long long)rand()*rand()%x+1;
} */

void insert(int &x,int goal)
{
	if(x==0){
		
		x=++cnt;
//		cout<<"insert"<<goal<<" "<<x<<" "<<root<<endl;
		tree[x].size=1;
		tree[x].data=goal;
		tree[x].val=(rand()*rand())%20040610;
		return ;
	}
	tree[x].size++;
	if(goal>=tree[x].data){
		insert(rs,goal);
	}else{
		insert(ls,goal);
	}
	if(ls!=0&&tree[x].val>tree[ls].val){
		
		rotate_r(x);
//		cout<<ls<<" "<<x<<"Rl"<<root<<endl;
	}
	if(rs!=0&&tree[x].val>tree[rs].val){
		rotate_l(x);
//		cout<<x<<"Ll"<<root<<endl;
	}
	pushup(x);
}

void del(int &x,int goal)
{
	/*if(x==0){
		return;
	}*/
//	cout<<x<<" "<<tree[x].data<<" "<<ls<<" "<<rs<<" "<<goal<<"del\n";
	tree[x].size--;
	if(tree[x].data==goal){
//		cout<<"ddddddddddddd\n";
		if(ls==0&&rs==0){
//			cout<<"-----"<<x<<endl;
			x=0;
			return;
		}else if(ls==0||rs==0){
			x=ls+rs;
//			cout<<"++++"<<x<<endl;
			return;
		}
		if(tree[ls].val<tree[rs].val){
			rotate_r(x);
			del(rs,goal);
			return;
		}else{
			rotate_l(x);
			del(ls,goal);
			return;
		}
	}
	if(tree[x].data>=goal){
//		cout<<"dell\n";
		del(ls,goal);
	}else{
//		cout<<"delr\n";
		del(rs,goal);
	}
	pushup(x);
}

int kth(int x,int goal)
{
	if(x==0){
		return 0;
	}
	if(goal<=tree[x].data){
		return kth(ls,goal);
	}else{
		return tree[ls].size+1+kth(rs,goal);
	}
}

int query(int x,int k)
{
	if(k==tree[ls].size+1){
		return tree[x].data;
	}else if(k<tree[ls].size+1){
		return query(ls,k);
	}else{
		return query(rs,k-tree[ls].size-1);
	}
}

int pre(int x,int goal)
{
	if(x==0){
		return 0;
	}
	if(tree[x].data>=goal){
		return pre(ls,goal);
	}else{
		int rnum=pre(rs,goal);
		if(rnum==0){
			return tree[x].data;
		}else{
			return rnum;
		}
	}
}

int succ(int x,int goal)
{
//	cout<<x<<" "<<ls<<" "<<rs<<"succ\n";
	if(x==0){
		return 0;
	}
	if(tree[x].data<=goal){
//		cout<<"0\n";
		return succ(rs,goal);
	}else{
		int lnum=succ(ls,goal);
		if(lnum==0){
//			cout<<"1\n";
			return tree[x].data;
		}else{
//			cout<<"2\n";
			return lnum;
		}
	}
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	memset(tree,0,sizeof(tree));
	srand(71806291);
	cin>>T;
	for(int nt=1;nt<=T;++nt){
		int opt=read(),xx=read();
		switch(opt){
			case 1:
				insert(root,xx);
//				cout<<root<<"root"<<endl;
				break;
			case 2:
				del(root,xx);
//				cout<<root<<"root"<<endl;
				break;
			case 3:
//				cout<<root<<"root"<<endl;
				cout<<kth(root,xx)+1<<endl;
				break;
			case 4:
//				cout<<root<<"root"<<endl;
				cout<<query(root,xx)<<endl;
				break;
			case 5:
//				cout<<root<<"root"<<endl;
				cout<<pre(root,xx)<<endl;
				break;
			case 6:
//				cout<<root<<"root"<<endl;
				cout<<succ(root,xx)<<endl;
				break;
		}
	}
	return 0;
}
//旋转treap 