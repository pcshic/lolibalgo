#include <iostream>
using namespace std;

// ret = b^p mod m
long long BM(int b, int p, int m) {
	if (p == 0) return 1;
	if (p&1) return ((b % m) * BM(b, p-1, m)) % m;
	long long res = BM(b, p>>1, m)%m;
	return (res * res)%m;
}

int main () {
	int B, P, M;
	while(cin >> B >> P >> M)
		cout << BM(B, P, M) << endl;
}