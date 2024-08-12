#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

using namespace std;
const int MAXN=300005;
vector<int> ch[MAXN];
int tin[MAXN], tout[MAXN], id[MAXN], par[MAXN];
int T = 0;
int n,q,fa[MAXN],p[MAXN],x,y;

const int MAXN=300005;
//有根树
class Tree
{
	int n,root,T;
	int fa[MAXN];
	vector<int> ch[MAXN];
	vector<int> e[MAXN];//因为是有根树，所以用fa、ch这个父子关系就够了，不需要引入e这个边关系
	int tin[MAXN],tout[MAXN];
	int v[MAXN];
	Tree(int _n, int _root):n(_n),root(_root)
	{
		for(int i=1;i<=n;i++)tin[i]=tout[i]=v[i]=-1;
	}
	int size(){return n;}
	int root(){return root;}
	void cptTime()
	{
		T=0;
		dfs(root,root);
	}
	void dfs(int u, int p)//计算时间戳,部分函数使用前需要调用过该函数且从调用到使用函数期间树的结构无变化
	{
		id[u] = tin[u] = tout[u] = T++;
		for (auto v : ch[u])
		{
			if (v != p)
			{
				dfs(v, u);
				tout[u] = tout[v];
			}
		}
	}
}
bool is_leaf(int u)
{
	return ch[u].empty();
}

bool is_ancestor(int u, int v)//即v是否在以u为根的子树中 本身O(1) 需要预处理函数cptTime（cptTime是O(n)的，因此该函数一次处理要使用n次以上，这样才是赚的）
{
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void solution()
{
	cin>>n;
	fa[1]=0;
	for (int i = 0; i <= n; i++)
		ch[i].clear();
	for (int i = 2; i <= n; i++)
	{
		cin >> fa[i];
		ch[fa[i]].push_back(i);
	}
}

	
