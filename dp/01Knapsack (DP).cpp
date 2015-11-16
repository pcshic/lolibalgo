#include <iostream>
#include <algorithm>
using namespace std;
#define INF 2147483647
#define N 101

int main() {
	int v, c, n, p[N];
	// v(olumn), c(profit), n(from 1...n)
	while (cin >> n) {
		fill(p, p + N, -INF);
		p[0] = 0;
		while (n--) {
			cin >> v >> c;
			for (int i = N - 1; i >=  v; --i)
				p[i] = max(p[i], p[i - v] + c);
		}
		cout << *max_element(p, p + N) << endl;
	}
}