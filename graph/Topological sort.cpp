#include <iostream>
#include <stack>
using namespace std;
#define N 102

bool adj[N][N], v[N];
int n;
stack<int> order;
void DFS(int s) {
	if (v[s]) return;
	for (int i = 1 ; i <= n ; ++i) if (adj[s][i]) DFS(i);
	v[s] = 1;
	order.push(s);
}
int main() {
	int m, a, b;
	// n tasks(from 1...n), m orders
	while (cin >> n >> m, n + m) {
		for (int i = 1 ; i <= n ; ++i) { v[i] = 0; for (int j = 0 ; j <= n ; ++j) adj[i][j] = 0; }
		for (int i = 0 ; i < m ; ++i) cin >> a >> b, adj[a][b] = 1;
		for (int i = 1 ; i <= n ; ++i) if (!v[i]) DFS(i);
		while (!order.empty()) { cout << ' ' << order.top(); order.pop(); }
		cout << endl;
	}
}