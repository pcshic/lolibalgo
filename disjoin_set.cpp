/**
by lwc
**/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MAXN 10001

int Group[MAXN], Group_num[MAXN];

inline int find(int k)
{
	return Group[k] == k ? Group[k] : (Group[k] = find(Group[k]));
}

inline void Union(int x, int y)
{
	int xx = find(x), yy = find(y);
	if(xx == yy)
		return;
	if(sz[xx] > sz[yy])
		swap(xx, yy);
	Group[xx] = yy;
	sz[xx] = 0;
	sz[yy] += sz[xx];
}

int main()
{
	//initial
	for (int i = 1; i <= 10001; ++i)
		f[i] = i;
}
