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

	void MakeSet(int N)
	{
		for (int i = 0; i < N; ++i)
			Rank[ Group[i] = i ] = 0;
	}

	int Find(int k)
	{
		return Group[k] == k ? Group[k] : Group[k] = Find(Group[k]);
	}

	void Union(int x, int y)
	{
		int xx = Find(x), yy = Find(y);
		if(xx == yy)
			return;
		if(Rank[xx] < Rank[yy])
			Group[xx] = yy;
		else if(Rank[xx] > Rank[yy])
			Group[yy] = xx;
		else
			Rank[ Group[yy] = xx ]++;
	}
};

DisjointSet <10001> ds;

int main()
{
	ds.MakeSet(n+1);
	ds.Union(1, 2);
	ds.Find(1);
}
