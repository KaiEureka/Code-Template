#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
int n,m,x,y,k,M;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
   	return x*f;
}
const int MaxN=100000+5;
int a[MaxN],Nmax=-1;
struct node
{
	int l,r,sum,add,mul;
	node(){l=r=sum=add=0,mul=1;}
	node(int L,int R,int SUM,int ADD,int MUL){l=L;r=R;sum=SUM;add=ADD;mul=MUL;}
}tr[MaxN*4];
//x是节点编号，根据完全二叉树的性质可知，x节点的左右子节点编号为x*2，x*2+1
void _build(int x,int l,int r)
{
	tr[x].l=l,tr[x].r=r;//节点表示区间的左右界    
	if(l==r)
	{
        //若l=r，说明这个节点是叶子节点，直接赋值        
		tr[x].sum=a[l];//a是原数列   
		Nmax=max(Nmax,x);     
		return;
    }
	int mid=(l+r)/2;//mid表示左右子区间的间隔    		
	_build(x<<1,l,mid),_build((x<<1)+1,mid+1,r);//递归建树   
	tr[x].sum=(tr[x<<1].sum+tr[(x<<1)+1].sum)%M;//pushup操作
}
inline void build(int r){_build(1,1,r);}
//区间查询
inline void pushdown(int now)
{	//先乘后加
	//(x*a+b)*c+d=x*ac+bc+d
	if(tr[now].add==0&&tr[now].mul==1)return;

	tr[now<<1].mul=tr[now<<1].mul*tr[now].mul%M;
	tr[(now<<1)+1].mul=tr[(now<<1)+1].mul*tr[now].mul%M;

	tr[now<<1].add=(tr[now<<1].add*tr[now].mul+tr[now].add)%M;
	tr[(now<<1)+1].add=(tr[(now<<1)+1].add*tr[now].mul+tr[now].add)%M;

	tr[now<<1].sum=(tr[now<<1].sum*tr[now].mul+tr[now].add*(tr[now<<1].r-tr[now<<1].l+1))%M;
	tr[(now<<1)+1].sum=(tr[(now<<1)+1].sum*tr[now].mul+tr[now].add*(tr[(now<<1)+1].r-tr[(now<<1)+1].l+1))%M;

	tr[now].add=0;tr[now].mul=1;
}
int _query(int x,int l,int r)
{
    if(tr[x].l>=l&&tr[x].r<=r) return tr[x].sum;//如果该节点的区间被要查找的区间包括了，那么就不用继续找了，直接返回改节点的值就行了
    pushdown(x);
	int mid=(tr[x].l+tr[x].r)>>1;
    int sum=0;
    if(l<=mid&&r>=tr[x].l) sum+=_query(x<<1,l,r);//如果当前节点在要查找区间左边界的右面，那么递归查找左子树
    if(r>=mid+1&&l<=tr[x].r) sum+=_query((x<<1)+1,l,r);//如果当前节点在要查找区间右边界的左面，那么递归查找右子树
    return sum;//由此得出了该区间的值，返回即可
}
inline int query(int l,int r){return _query(1,l,r);}
//单点修改
void _change(int now,int x,int k)
{
	if(tr[now].l==tr[now].r){tr[now].sum=k;return;}
	pushdown(x);
	int mid=(tr[now].l+tr[now].r)>>1;
	if(x<=mid)_change((now<<1),x,k);
	else _change((now<<1)+1,x,k);
	tr[now].sum=(tr[now<<1].sum+tr[(now<<1)+1].sum)%M;
}
inline void change(int x,int k){_change(1,x,k);}
//某节点被打了懒惰标记表示它本身修改了，但他的子节点尚未修改
void _update(int now,int l,int r,int k)
{
	if(r<tr[now].l||l>tr[now].r)return;
	if(l<=tr[now].l&&tr[now].r<=r)
	{
		tr[now].sum=(tr[now].sum+k*(tr[now].r-tr[now].l+1))%M;//先修改这个区间
        tr[now].add=(tr[now].add+k)%M;//然后给它打上懒标记
		return;
	}
	pushdown(now);
	int mid=(tr[now].l+tr[now].r)/2;
	if(l<=mid&&r>=tr[now].l)_update(now<<1,l,r,k);
	if(r>=mid+1&&l<=tr[now].r)_update((now<<1)+1,l,r,k);
	tr[now].sum=(tr[now<<1].sum+tr[(now<<1)+1].sum)%M;
	//如果是叶节点，标记会被下传到不会被访问到的虚空节点去，便相当于是消除标记了，因而无需单独特判叶节点
}
void __update(int now,int l,int r,int k)
{
	if(r<tr[now].l||l>tr[now].r)return;
	if(l<=tr[now].l&&tr[now].r<=r)
	{
		tr[now].sum=tr[now].sum*k%M;//先修改这个区间
		tr[now].add=tr[now].add*k%M;//然后给它打上lazytag并更新lazytag
        tr[now].mul=tr[now].mul*k%M;
		return;
	}
	pushdown(now);
	int mid=(tr[now].l+tr[now].r)/2;
	if(l<=mid&&r>=tr[now].l)__update(now<<1,l,r,k);
	if(r>=mid+1&&l<=tr[now].r)__update((now<<1)+1,l,r,k);
	tr[now].sum=(tr[now<<1].sum+tr[(now<<1)+1].sum)%M;
	//如果是叶节点，标记会被下传到不会被访问到的虚空节点去，便相当于是消除标记了，因而无需单独特判叶节点
}
void updateofadd(int l,int r,int k){_update(1,l,r,k);}
void updateofmul(int l,int r,int k){__update(1,l,r,k);}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&M);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	build(n);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&x);
		if(x==1)
		{
			scanf("%lld%lld%lld",&x,&y,&k);
			updateofmul(x,y,k);
			/*
			for(int i=1;i<=Nmax;i++)
			{
				cout<<"修改后的树"<<tr[i].l<<' '<<tr[i].r<<' '<<tr[i].sum<<endl;
				cout<<endl;
			}
			*/
		}
		else if(x==2)
		{
			scanf("%lld%lld%lld",&x,&y,&k);
			updateofadd(x,y,k);
		}
		else
		{
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",query(x,y)%M);
		}
	}
	return 0;
}

/*简化线段树
#include <iostream>
const long long N = 1e6 + 10;
using namespace std;

long long  m, k, q;
long long a[N], b[N];
//线段树
#define lson rt << 1
#define rson rt << 1 | 1
long long n;
long long c[N];
//n is the number of elements in the array

void inner_build(long long rt, long long l, long long r)
{
	if (l == r)
	{
		c[rt] = 0;
		return;
	}
	long long mid = (l + r) >> 1;
	inner_build(lson, l, mid);
	inner_build(rson, mid + 1, r);
}
inline void build(){inner_build(1, 1, n);}

void pushdown(long long rt, long long l, long long r)
{
	long long mid = (l + r) >> 1;
	if (c[rt])
	{
		c[lson] += c[rt];
		c[rson] += c[rt];
		c[rt] = 0;
	}
}

void inner_change(long long rt, long long l, long long r, long long x, long long y, long long z)
{
	if (x <= l && r <= y)
	{
		c[rt] += z;
		return;
	}
	pushdown(rt, l, r);
	long long mid = (l + r) >> 1;
	if (x <= mid)
		inner_change(lson, l, mid, x, y, z);
	if (y > mid)
		inner_change(rson, mid + 1, r, x, y, z);
}
inline void change(int x,int y,int z){inner_change(1,1,n,x,y,z);}

long long inner_query(long long rt, long long l, long long r, long long x)
{
	if (l == r)
		return c[rt];
	pushdown(rt, l, r);
	long long mid = (l + r) >> 1;
	if (x <= mid)
		return inner_query(lson, l, mid, x);
	else
		return inner_query(rson, mid + 1, r, x);
}
inline long long query(long long x){return inner_query(1,1,n,x);}
*/