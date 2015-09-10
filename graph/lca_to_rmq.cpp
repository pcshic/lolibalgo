/**
by lwc
**/
#include <bits/stdc++.h>
using namespace std;
#define N 100001
#define LOGN 19   //needs to be floor(log(2N)) + 1

template<int _MAXN, int _MAXLOGN> class LCA2RMQ {
public:
	struct Edge {
    	int x;
    	Edge(int a=0):
        	x(a) {}
	};
	int rmq[_MAXLOGN][_MAXN<<1];
	int vs[_MAXN<<1], d[_MAXN<<1], first[_MAXN];
	vector <Edge> e[_MAXN];
	int cnt;
	inline void init(int n) {
		for (int i = 0; i <= n; ++i)
			e[i].clear();
		cnt = 0;
	}
	inline void addedge(int x, int y) {
		e[x].push_back(Edge(y));
	}
	void dfs(int k, int dep, int pa) {
		first[k] = cnt, d[cnt] = dep, vs[cnt++] = k;
		for (auto &i : e[k]) {
			if(i.x != pa) {
				dfs(i.x, dep+1, k);
				d[cnt] = dep;
				vs[cnt++] = k;
			}
		}
	}
	inline void initRMQ() {
		for (int i = 0; i < cnt; ++i)
			rmq[0][i] = i;
		for (int j = 1; (1<<j) <= cnt; ++j)
			for (int i = 0; i+(1<<j) <= cnt; ++i)
				rmq[j][i] = d[rmq[j-1][i]] < d[rmq[j-1][i+(1<<(j-1))]] ? rmq[j-1][i] : rmq[j-1][i+(1<<(j-1))];
	}
	inline int query(int a, int b) {
		int k = __builtin_clz((int)1)-__builtin_clz(b-a+1);
		return d[rmq[k][a]] < d[rmq[k][b-(1<<k)+1]] ? rmq[k][a] : rmq[k][b-(1<<k)+1];
	}
	inline int find_lca(int a, int b) {
		if(first[a] > first[b])
			swap(a, b);
		return vs[query(first[a], first[b])];
	}
};

// define
// LCA2RMQ<N, LOGN> lca;

// initialize (n = number of nodes)
// lca.init(n);

// press the tree
// lca.dfs(root, depth, father);

// build rmq
// lca.initRMQ();

// find lca of a, b
// lca.find_lca(a, b);

