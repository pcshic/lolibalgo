#include <vector>
#include <queue>
#include <functional>
using namespace std;
#define Inf 1000000000
#define V 10

typedef pair<int, int> P;

vector<P > edge; // (to, cost)
int cost[V][V], mincost[V];
// O(|E|log|V|) N vertices
int Prim(int N) {
	int ret = 0;
	priority_queue<P, vector<P >, greater<P > > pq; // (w, Vi)
	for (int i = 0 ; i < N ; ++i) mincost[i] = Inf;
	mincost[0] = 0;
	pq.push(make_pair(0, 0));
	while (!pq.empty()) {
		P p = pq.top(); pq.pop();
		int v = p.second;
		if (mincost[v] < p.first) continue;
		ret += p.first;
		for (int i = 0 ; i < edge.size() ; ++i) {
			int b = edge[i].first;
			if (mincost[b] > cost[v][b])
				mincost[b] = cost[v][b], pq.push(make_pair(cost[v][b], b));
		}
	}
	return ret;
}