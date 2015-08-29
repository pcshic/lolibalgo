#include <bits/stdc++.h>
using namespace std;

template<typename E, bool FUNC(E, E)> class SparseTableRMQ {
public:
	static const int MAXN = 524288;
	static const int MAXLOGN = 20;
	E A[MAXN];
	int fa[MAXLOGN][MAXN];
	void build(int n) {
		for (int i = 0; i <= n; i++)
			fa[0][i] = i;
		for (int i = 1; (1<<i) <= n; i++) {
			for (int j = 0; i+j <= n; j++) {
				int a = fa[i-1][j], b = fa[i-1][j+(1<<(i-1))];
				fa[i][j] = A[a] > A[b] ? a : b;
			}
		}
	}
	int query(int l, int r) {	// return maximum position
		int p = __builtin_clz((int)1) - __builtin_clz(r-l+1);
		int a = fa[p][l], b = fa[p][r-(1<<p)+1];
		return A[a] > A[b] ? a : b;
	}
};

// example
bool cmp(int a, int b) { return a >= b; }
SparseTableRMQ<int, cmp>  TT;

int main() {
	int N = 9;
	int A[10] = {0, 3, 2, 4, 5, 6, 8, 1, 9, 7};
	for (int i = 0; i <= N; i++)
		TT.A[i] = A[i];
	TT.build(N);
	printf("%d\n", TT.query(0, 9));	// max(A[0, 9]) = A[8]
	printf("%d\n", TT.query(0, 2));	// max(A[0, 2]) = A[1]
	return 0;
}

