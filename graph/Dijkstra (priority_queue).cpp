#include <queue>
#include <functional>
#include <vector>
using namespace std;
#define Inf 1000000000
#define V

typedef pair<int, int> P;
vector<P > edge; // (to, cost)
int d[V];
// O(|E|log|V|) from s and N vertices
void dijkstra(int s, int N) {
	priority_queue<P, vector<P>, greater<P> > pq; // greater<T> -> #include <funtional>
	for (int i = 0 ; i < N ; ++i) d[i] = Inf;
	d[s] = 0;
	pq.push(make_pair(0, s));
	while (!pq.empty()) {
		P p = pq.top(); pq.pop();
		int v = p.second;
		if (d[v] < p.first) continue;
		for (int i = 0 ; i < edge.size() ; ++i) {
			int b = edge[i].first, c = edge[i].second;
			if (d[b] >= d[v] + c)
				d[b] = d[v] + c, pq.push(make_pair(d[b], b));
		}
	}
}