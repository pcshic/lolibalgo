#include <bits/stdc++.h>
using namespace std;
template<typename WTYPE, int MAXN, bool FUNC(WTYPE, WTYPE)> 
class MST {
public:
	struct Edge {
    	int x, y;
		WTYPE v;
    	Edge(int a=0, int b=0, WTYPE c=0):
        	x(a), y(b), v(c) {}
    	bool operator<(const Edge &a) const {
    		return FUNC(v, a.v);
    	}
	};
	vector<Edge> e, mst;
	int N, p[MAXN], rank[MAXN];
	WTYPE cost; 
	void init(int n) {
		N = n;
		for(int i = 0; i <= N; i++)
	        p[i] = i, rank[i] = 1;
	    e.clear(), mst.clear();
	}
	void addedge(int x, int y, WTYPE w) {
		e.push_back(Edge(x, y, w));
	}
	int kruscal() {
		sort(e.begin(), e.end());
		cost = 0;
	    for(int i = 0; i < e.size(); i++) {
	        if(joint(e[i].x, e[i].y))
	        	mst.push_back(e[i]), cost += e[i].v;
	    }
	    return mst.size() == N-1;
	}
	int findp(int x) {
	    return p[x] == x ? x : (p[x] = findp(p[x]));
	}
	int joint(int x, int y) {
	    x = findp(x), y = findp(y);
	    if(x == y)
	        return 0;
	    if(rank[x] > rank[y])
	        rank[x] += rank[y], p[y] = x;
	    else
	        rank[y] += rank[x], p[x] = y;
	    return 1;
	}
};
bool cmp(int a, int b) { return a < b; }
MST<int, 32767, cmp> mst;

int main() {
	int n, m, q;
	int x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		mst.init(n);	// vertex [0, n-1]
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			x--, y--;
			mst.addedge(x, y, w);
		}
		mst.kruscal();
		
		for (auto e : mst.mst)
			printf("%d - %d %d\n", e.x, e.y, e.v);
	}
	return 0;
}
/*
5 7
1 2 3
1 5 1
2 3 5
2 5 4
3 5 6
3 4 2
4 5 7
*/

