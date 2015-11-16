#include <iostream>
using namespace std;
#define V

int d[V][V];
// O(|V|^3) N vertices
void floyd_warshall(int N) {
	for (int k = 0 ; k < N ; ++k)
		for (int i = 0 ; i < N ; ++i)
			for (int j= 0 ; j < N ; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}