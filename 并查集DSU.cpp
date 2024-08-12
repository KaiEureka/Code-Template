#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <list>
#define int long long
#define i32 signed
#define endl '\n'
using namespace std;

const int MaxN=50005;
int fa[MaxN],Rank[MaxN],Peo[MaxN];
inline int find(int x) {return (fa[x] == x) ? x :  fa[x]=find(fa[x]);}
inline void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (Rank[x] > Rank[y])
	{
		fa[y] = x;
		Peo[x] += Peo[y];
	}
	else
	{
		fa[x] = y;
		Peo[y] += Peo[x];
		if (Rank[x] == Rank[y]) //树高相同时让父节点的树高值加一
			Rank[y] += 1;
	}
}
inline void init(int n)
{
	for(int i=1;i<=n;i++)
	{
		fa[i] = i;
		Rank[i]=1;
		Peo[i]=1;
	}
}

void solution()
{

}

i32 main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)
	{
		input();
		initilization();
		solution();
	}
	return 0;
}