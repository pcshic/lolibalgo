#include <iostream>
#include <algorithm>
using namespace std;
#define N 101

int main() {
	int v[N], c[N], n; 
	// v(olumn), c(profit), n(from 0...n-1), m(a)xp(rofit), t(otal)v(olumn)
	while (cin >> n) {
		for (int i = 0 ; i < n ; ++i) cin >> v[i] >> c[i];
		int mxp = 0;
		for (int i = 0 ; i < (1 << n) ; ++i) {
			int tv = 0, p = 0;
			for (int j = 0 ; j < n ; ++j)
				if((1 << j) & i)
					tv += v[j], p += c[j];
			if (tv <= 100) mxp = max(mxp, p);
		}
		cout << mxp << endl;
	}
}