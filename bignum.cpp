#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

class BigInt {
	friend ostream& operator << (ostream& os, const BigInt& r);
	friend istream& operator >> (istream& is, BigInt& r);
	friend BigInt abs (const BigInt& r);

	static const ll m = 1ll<<32;
	static const int w = 32;
	static BigInt mod;
	int sgn;
	vector <uint> mag;

	BigInt& shl (uint sh) {
		ull c = 0;
		for (int i=0; i<mag.size(); i++) {  
			c += (ull)mag[i] << sh;
			mag[i] = (uint)c;
			c >>= w;
		}
		if (c) mag.push_back((uint)c);
		return *this;
	}

	BigInt& shr (uint sh) {
		ull c = 0;
		for (int i=mag.size()-1; i>=0; i--) {
			c += mag[i];
			mag[i] = (uint)(c >> sh);
			c <<= w;
		}
		reduce();
		return *this;
	}

	int cmp (const BigInt& r, int e=0) const{
		int i, rs = (mag.size() > r.mag.size()+e) - (mag.size() < r.mag.size()+e);
		if (rs) return rs;
		for (i=mag.size()-1; i>=e; i--)
			if (mag[i] != r.mag[i-e])
				rs = (mag[i] > r.mag[i-e] ? 1:-1);
		for (; i>=0; i--)
			if (mag[i]) return 1;
		return 0;
	}

	void add (const BigInt& r, int e=0) {
		int i, mn, sz, rsz;
		ll c = 0;
		for (i=min(e,mag.size()); i<e; i++)
			mag.push_back(0);
		mn = min (sz = mag.size(), rsz = r.mag.size()+e);
		for (; i<mn; i++) {
			c += (ll)mag[i] + r.mag[i-e];
			mag[i] = (uint)c;
			c >>= w;
		}
		for (; i<rsz; i++) {
			c += r.mag[i-e];
			mag.push_back ((uint)c);
			c >>= w;
		}
		for (; i<sz; i++) {
			c += mag[i];
			mag[i] = (uint)c;
			c >>= w;
		}
		if (c)
			mag.push_back ((uint)c);
	}

	void reduce () {
		while (mag.size() > 1 && mag.back() == 0)
			mag.erase (mag.end() - 1);
		if (mag.size() == 1 && mag.back() == 0)
			sgn = 0;
	}

	void sub (const BigInt& r, int e=0) {
		int i, rsz = r.mag.size()+e;
		ll c = 0;
		for (i=e; i<rsz; i++) {
			c += (ll)mag[i] + m - r.mag[i-e];
			mag[i] = (uint)c;
			c >>= w;
			c--;
		}
		if (c) mag[i] += (int)c;
		reduce();
	}

	BigInt& mul (uint n) {
		if (n == 0) return *this = 0;
		ull c = 0;
		for (int i=0; i<(signed)mag.size(); i++) {
			c += (ll)mag[i] * n;
			mag[i] = (uint)c;
			c >>= w;
		}
		if (c)
			mag.push_back ((uint) c);
		return *this;
	}

	uint div (uint n) {
		ull l = 0;
		for (int i=mag.size()-1; i>=0; i--) {
			(l <<= w) += mag[i];
			mag[i] = (uint)(l / n);
			l %= n;
		}
		reduce ();
		return (uint)l;
	}

	BigInt& div (BigInt r) {
		ull l1, r1=0;
		if (r.mag.size()==1) {
			mod = div (r.mag[0]);
			return *this;
		}
		uint e=0, q, sh;
		mag.swap (mod.mag);
		while (mod.cmp(r,e) >= 0) e++;
		if (e == 0) return *this = 0;
		r1 = r.mag.back();
		for (sh=0; ~r1 & 0x80000000; sh++)
			r1 <<= 1;
		mod.shl(sh);
		r.shl(sh);
		r1= r.mag.back();
		BigInt p;
		mag.clear();
		while (e--) {
			q = 0;
			if (mod.cmp(r,e) >= 0) {
				((l1 = mod[r.mag.size()+e])<<= w) += mod[r.mag.size()+e-1];
				q = (uint)(l1 / (r1 + 1));
				mod.sub ((p=r).mul (q), e);
				while (mod.cmp(r,e) >=0) {
					mod.sub (r, e);
					q++;
				}
			}
			mag.insert (mag.begin(),q);
		}
		mod.shr(sh);
		reduce();
		return *this;
	}

public:
	BigInt (int n=0) : sgn((n>0) - (n<0)) {
		mag.push_back(abs(n));
	}

	BigInt (uint n) : sgn(n > 0) {
		mag.push_back((uint) n);
	}

	uint size () const {
		return mag.size();
	}

	uint operator [] (uint i) {
		return i >= mag.size() ? 0 : mag[i];
	}

	BigInt& operator <<= (uint sh) {
		mag.insert (mag.begin(), sh / w, 0);
		return shl (sh % w);
	}

	BigInt operator << (uint sh) {
		BigInt l = *this;
		return l <<= sh;
	}

	BigInt& operator >>= (uint sh) {
		mag.erase (mag.begin(), mag.begin() + sh / w);
		return shr (sh % w);
	}

	BigInt operator >> (uint sh) {
		BigInt l = *this;
		return l >>= sh;
	}

	bool operator < (const BigInt& r) const {
		if (sgn != r.sgn) return sgn < r.sgn;
		return (cmp(r) < 0) ^ (sgn < 0);
	}

	bool operator == (const BigInt& r) const {
		return sgn == r.sgn && cmp(r) == 0;
	}

	bool operator != (const BigInt& r) const {
		return !(*this == r);
	}

	BigInt& operator += (const BigInt& r) {
		if (r.sgn == 0) return *this;
		if (sgn == 0) return *this = r;
		if (sgn + r.sgn == 0) {
			int comp = cmp (r);
			if (comp == 0) return *this = 0;
			if (comp < 0) {
				BigInt d = r;
				d.sub(*this);
				*this = d;
			} else
				sub (r);
		} else
			add (r);
		return *this;
	}

	BigInt operator + (BigInt r) const {
		return r += *this;
	}

	BigInt& operator -= (const BigInt& r) {
		sgn = -sgn;
		*this += r;
		sgn = -sgn;
		return *this;
	}

	BigInt operator - (BigInt r) const {
		r.sgn = -r.sgn;
		return r += *this;
	}

	BigInt operator * (const BigInt& r) const {
		BigInt p, p1;
		p = 0;
		p.sgn = sgn * r.sgn;
		if (p.sgn == 0) return p;
		for (unsigned i=0; i<r.mag.size(); i++) {
			p.add ((p1=*this).mul (r.mag[i]), i);
		}
		return p;
	}

	BigInt& operator *= (const BigInt& r) {
		return *this = *this * r;
	}

	BigInt& operator /= (const BigInt& r) {
		mod.sgn = sgn *= r.sgn;
		div (r);
		return *this;
	}

	BigInt operator / (const BigInt& r) const {
		BigInt q = *this;
		return q /= r;
	}

	BigInt& getmod () {
		return mod;
	}

	BigInt& operator %= (const BigInt& r) {
		*this /= r;
		mod.swap (*this);
		return *this;
	}

	BigInt operator % (const BigInt& r) const {
		BigInt l = *this;
		return l %= r;
	}

	void swap (BigInt& r) {
		mag.swap (r.mag);
		std::swap (sgn, r.sgn);
	}
};

BigInt BigInt::mod;

ostream& operator << (ostream& os, const BigInt& r) {
	string s, s9;
	uint d9;
	int i;
	BigInt l = r;
	while (d9 = l.div (1000000000), l != 0) {
		for (i=0; i<9; i++) {
			s9.insert (0, 1, char(d9%10+'0'));
			d9 /= 10;
		}
		s.insert (0, s9);
		s9.clear();
	}
	do {
		s9.insert (0, 1, char(d9%10+'0'));
		d9 /= 10;
	} while (d9);
	if (r.sgn < 0) os << '-';
	os << s9 << s;
	return os;
}

istream& operator >> (istream& is, BigInt& r) {
	ws (is);
	int d9 = 0, nd = 0, sign = 1;
	if (is.peek()=='-' || is.peek()=='+') {
		if (is.peek()=='-') sign = -1;
		cin.ignore();
	}
	r = 0;
	while (isdigit(is.peek())) {
		(d9 *= 10) += is.get() - '0';
		if (++nd == 9) {
			r.mul (1000000000) .add (d9);
			d9 = nd = 0;
		}
	}
	while (nd--) r.mul (10);
	r.add (d9);
	if (r.mag.size()>1 || r.mag[0]>0)
		r.sgn = sign;
	return is;
}

BigInt abs (const BigInt& r) {
	BigInt n = r;
	n.sgn *= n.sgn;
	return n;
}
