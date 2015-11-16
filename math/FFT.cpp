#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1 << 18;
const double pi = acos(-1.0);

typedef struct complex {
	double r, i;
	complex(double real = .0, double imaginary = .0) { r = real, i = imaginary; }
	complex operator+(const complex& o) const { return complex(r + o.r, i + o.i); }
	complex operator-(const complex& o) const { return complex(r - o.r, i - o.i); }
	complex operator*(const complex& o) const { return complex(r * o.r - i * o.i, r * o.i + i * o.r); }
};

 //rev true FFT, false IFFT
void FFT(complex* a, complex* A, int n, bool rev) {
    int lg2n = int(log(double(n))/log(2.0)+.5), x;
    for (int i = 0 ; i < n ; ++i) {
        x = 0;
        for (int j = 0 ; j < lg2n; ++j)
            if(i&(1<<j)) x += (1<<(lg2n-1 - j));
        A[x] = a[i];
    }
    for (int s = 1 ; s <= lg2n ; ++s) {
        int m = 1<<s;
        double p = 2.0 * (rev ? -1 : 1) * pi / m;
        complex wm(cos(p), sin(p));
        for (int k = 0 ; k < n ; k += m) {
            complex w(1);
            for (int j = 0 ; j < m/2 ; ++j) {
                complex t = w * A[k+j+m/2];
                A[k+j+m/2] = A[k+j];
                A[k+j] = A[k+j] + t;
                A[k+ j+m/2] = A[k+j+m/2] - t;
                w = w*wm;
            }
        }
    }
    if (rev) {
        complex tmp(1.0/n, 0.0);
        for (int i = 0 ; i < n ; ++i) A[i] = A[i] * tmp;
    }
}

complex a[maxn], b[maxn], c[maxn], A[maxn], B[maxn], C[maxn];
int out[maxn], n;
char str[maxn];
bool init() {
    if (scanf("%s", str) != 1) return false;
    int len1 = strlen(str);
    reverse(str, str + len1);
    for (int i = 0 ; i < len1 ; ++i) a[i] = complex(str[i] - '0', 0.0);
    scanf("%s", str);
    int len2 = strlen(str);
    reverse(str, str + len2);
    for (int i = 0 ; i < len2 ; ++i) b[i] = complex(str[i] - '0', 0.0);
    n = 1;
    while (len1 * 2 > n || len2 * 2 > n) n <<= 1;
    for (int i = len1 ; i < n ; ++i) a[i] = complex(0.0, 0.0);
    for (int i = len2 ; i < n ; ++i) b[i] = complex(0.0, 0.0);
    for (int i = 0 ; i < n ; ++i) c[i] = C[i] = A[i] = B[i] = complex(0.0, 0.0);
    return true;
}

int main() {
    while(init()) {
        FFT(a, A, n, false);
        FFT(b, B, n, false);
        for (int i = 0 ; i < n ; ++i) C[i] = A[i] * B[i];
        FFT(C, c, n, true);
        memset(out, 0, sizeof(out));
        for (int i = 0 ; i < n ; ++i) {
			int x = c[i].r + .5;
            out[i] += x;
            out[i + 1] += out[i]/10;
            out[i] %= 10;
        }
        while(n > 1 && !out[n - 1]) --n;
        for (int i = n - 1 ; i >= 0 ; --i) printf("%d", out[i]);
        printf("\n");
    }
}