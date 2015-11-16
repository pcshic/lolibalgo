#include <iostream>
using namespace std;
#define Inf 1000000000
#define V 10

int cost[V][V], d[V];
bool used[V];
// O(|V|^2) from s and N vertices
void dijkstra(int s, int N) {
	for (int i = 0 ; i < N ; ++i) d[i] = Inf, used[i] = false;
	d[s] = 0;
	while (true) {
		int v = -1;
		for (int u = 0 ; u < N ; ++u)
			if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
		if (v == -1) break;
		used[v] = true;
		for (int u = 0 ; u < N ; ++u)
			d[u] = min(d[u], d[v] + cost[v][u]);
	}
}