/**
by lwc
Path Compression + Union by rank
**/
#include <bits/stdc++.h>
using namespace std;

#define MAXN 10001

int Group[MAXN], Rank[MAXN];

inline int find(int k)
{
	return Group[k] == k ? Group[k] : Group[k] = find(Group[k]);
}

inline void Union(int x, int y)
{
	int xx = find(x), yy = find(y);
	if(xx == yy)
		return;
	if(Rank[xx] < Rank[yy])
		Group[xx] = yy;
	else if(Rank[xx] > Rank[yy])
		Group[yy] = xx;
	else
		Rank[ Group[yy] = xx ]++;
}

int main()
{
	//initial
	for (int i = 1; i <= 10001; ++i)
	{
		Group[i] = i;
		Rank[i] = 0;
	}
}
