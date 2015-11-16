/*
// T pow_mod(T a, T p, T n)
a^p mod n where 0 =< a < n
// gcd(T a, T b, T &d, T &x, T &y)
ax+by = d and min{|x|+|y|} where d = gcd(a, b) p.s. even if a, b belongs to int, x, y could be out of int
//T invmod(T a, T n)
a^(-1) ¡Ý b (mod n), ab ¡Ý 1 (mod n)
//T CRT(int n, int *a, int *m)
Chinese Reminder Theorem: x ¡Ý a[i] (mod m[i]) where 0 =< i < n
//int log_mod(int a, int b, int n)
a^x ¡Ý b (mod n), if n is prime return no solution (-1)
// int phi(int n)
eular_phi(n) = n(1-1/p1)(1-1/p2)...(1-1/pn) where gcd(pi, n) == 1 and i belongs to 1...n
// C(n, m)
C^n_m = n!/m!(n-m)!
*/
#include <iostream>
#include <cmath>
#include <map>
using namespace std;
typedef long long T;

T pow_mod(T a, T p, T n) {
	if (p == 0) return 1;
	T ret = pow_mod(a, p >> 1, n);
	ret = ret * a % n;
	if (p&1) ret = ret * a % n;
	return ret;
}

T gcd(T a, T b) { return (b == 0 ? a : gcd(b, a%b)); }
void gcd(T a, T b, T &d, T &x, T &y) {
	if (!b) d = a, x = 1, y = 0;
	else gcd(b, a%b, d, y, x), y -= x*(a/b);
}

T invmod(T a, T n) {
	T d, x, y;
	gcd(a, n, d, x, y);
	return (d == 1 ? (x + n) % n : -1);
}

T CRT(int n, int *a, int *m) {
	T M = 1, d, y, x = 0;
	for (int i = 0 ; i < n ; ++i) M *= m[i];
	for (int i = 0 ; i < n ; ++i) {
		T w = M / m[i];
		gcd(m[i], w, d, d, y);
		x = (x + y * w * a[i]) % M;
	}
	return (x + M) % M;
}

int log_mod(int a, int b, int n) {
	int m = sqrt(n+.5), v = invmod(pow_mod(a, m, n), n), e = 1;
	map<int, int> x;
	x[1] = 0;
	// calculate e[i]
	for (int i = 0 ; i < m ; ++i) {
		e = e * a % n;
		if (!x.count(e)) x[e] = i;
	}
	// consider a^(im), a^(im+1), ..., a^(im+m-1)
	for (int i = 0 ; i < m ; ++i) {
		if (x.count(b)) return i * m + x[b];
		b = b * v % n;
	}
	return -1;
}

int phi(int n) {
	int m = sqrt(n+.5), ret = n;
	for (int i = 2 ; i <= m ; ++i) {
		if (n % i == 0) {
			ret = ret / i * (i - 1);
			while (n % i  == 0) n /= i;
		}
	}
	if (n > 1) ret  = ret / n * (n - 1);
	return ret;
}

T C(int n, int m) {
	T res = 1;
	m = min(m, n-m);
	for (int i = 1 ; i <= m ; ++i)
		res = res * (n - i + 1) / i;
	return res;
}

#define N 10000
bool sieve[N];
void eratosthenes() {
	sieve[0] = sieve[1] = true;
	for (int i = 2 ; i <= N ; ++i)
		if (!sieve[i])
			for (int k = (N - 1)/i, j = i * k ; k >= i ; --k, j -= i)
				if (!sieve[k])
					sieve[j] = true;
}

int main() {
}