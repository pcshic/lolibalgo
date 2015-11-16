#include <iostream>
using namespace std;
#define Inf 1000000000
#define V 10

int cost[V][V], mincost[V];
bool used[V];
// O(|V|^2) N vertices
int Prim(int N) {
	for (int i = 0 ; i < N ; ++i) mincost[i] = Inf, used[i] = false;
	mincost[0] = 0;
	int res = 0;
	while (true) {
		int v = -1;
		for (int u= 0 ; u < N ; ++u)
			if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
		if (v == -1) break;
		used[v] = true;
		res += mincost[v];
		for (int u = 0 ; u < N ; ++u)
			mincost[u] = min(mincost[u], cost[v][u]);
	}
	return res;
}