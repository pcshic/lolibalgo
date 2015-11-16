#include <vector>
using namespace std;
#define Inf 1000000000
#define V

vector<pair<int, pair<int, int> > > edge;
int d[V];
// O(|V||E|) from s and N vertices
void BellmanFord(int s, int N) {
	for (int i = 0 ; i < N ; ++i) d[i] = Inf;
	d[s] = 0;
	while (true) {
		bool update = false;
		for (int i = 0 ; i < edge.size() ; ++i) {
			int c = edge[i].first, a = edge[i].second.first, b = edge[i].second.second;
			if (d[a] != Inf && d[b] >= d[a] + c) d[b] = d[a] + c, update = true; // i == V-1 -> negative cycle
		}
		if (!update) break;
	}
}