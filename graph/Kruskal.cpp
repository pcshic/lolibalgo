#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int p[100001];
int find(int x)  { return p[x] == x ? x : p[x] = find(p[x]); }
int main() {
	int n, m, a ,b ,c;
	while (cin >> n >> m) {
		long long int cost = 0;
		int edgecnt = 0;
		vector< pair<int, pair<int, int> > > edge;
		for (int i = 0 ; i < m ; ++i) cin >> a >> b >> c, edge.push_back(make_pair(c, make_pair(a, b)));
		sort(edge.begin(), edge.end());
		for (int i = 0 ; i < n ; ++i) p[i] = i;
		for (int i = 0 ; i < edge.size() ; ++i) {
			c = edge[i].first, a = edge[i].second.first, b = edge[i].second.second;
			int pa = find(a),  pb = find(b);
			if (pa != pb) ++edgecnt, cost += c, p[pa] = pb;
		}
		if (edgecnt == n-1) cout << cost << endl;
		else cout << -1 << endl;
	}
}