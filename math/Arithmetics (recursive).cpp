#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

// token (²Å¸¹)
string token, reads;
stringstream ss;

void get_token() {
	if (ss.peek() != '\n') ss >> token;
	else token = "";
}

// expression = term {("+"|"-") term} .
long long expression() {
	long long res = term();
	while (1) {
		if (token=="+") {
			get_token();
			res += term ();
		}
		else if (token=="-") {
			get_token();
			res -= term ();
		}
		else break;
	}
	return res;
}

// term = factor {("*"|"/"|"%") factor} .
long long term () {
	long long res = factor();
	while (1) {
		if (token=="*") {
			get_token();
			res *= factor();
		} 
		else if (token=="/") {
			get_token();
			res /= factor();
		}
		else if (token=="%") {
			get_token();
			res %= factor();
		}
		else break;
	}
	return res;
}

// factor = number | "(" expression ")" .
long long factor() {
	long long res;	
	if (token == "(") {
		get_token();
		res = expression ();
	}
	else res = atoll(token.c_str());
	get_token();
	return res;
}

int main() {
	int T;
	cin >> T >> ws;
	while (T--) {
		getline(cin, reads);
		for (int i = 1 ; i < reads.size() ; ++i)
			if (!(reads[i] <= '9' && reads[i] >= '0' && reads[i-1] <= '9' && reads[i-1] >= '0'))
				reads.insert(i++, " ");
		ss << reads;
		get_token();
		cout << expression() << endl;
		ss.clear();
	}
}