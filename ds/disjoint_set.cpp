/**
by lwc
Path Compression + Union by rank
**/
#include <bits/stdc++.h>
using namespace std;

template<int __MAXN> class DisjointSet
{
public:
	int Group[__MAXN], Rank[__MAXN];

	void MakeSet(int N) {
		for (int i = 0; i < N; ++i)
			Rank[ Group[i] = i ] = 0;
	}

	int Find(int k) {
		return Group[k] == k ? Group[k] : Group[k] = Find(Group[k]);
	}

	bool Union(int x, int y) {
		x = Find(x), y = Find(y);
		if(x == y)
			return 0;
		if(Rank[x] < Rank[y])
			Group[x] = y;
		else if(Rank[x] > Rank[y])
			Group[y] = x;
		else
			Rank[ Group[y] = x ]++;
		return 1;
	}
};

DisjointSet <10001> ds;

int main()
{
	ds.MakeSet(n+1);
	ds.Union(1, 2);
	ds.Find(1);
}
