#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

const string prec  = "+-*/";
string infix2postfix(string &infix) {
	stack<string>st;
	stringstream ss;
	string op, postfix = "";
	ss << infix;
	while (ss >> op) {
		if (op >= "0" && op <= "9") postfix += ' ' + op;
		else if (op == "(") st.push(op);
		else if (op == ")") {
			while (st.top() != "(") postfix += ' ' + st.top(), st.pop();
			st.pop();
		} else {
			while (!st.empty() && st.top() != "(" && prec.find(st.top())/2 >= prec.find(op)/2) postfix += ' ' + st.top(), st.pop();
			st.push(op);
		}
	}
	while (!st.empty()) postfix += ' ' + st.top(), st.pop();
	return postfix;
}

int calculate(string postfix) {
	int u, v;
	stack<int> st;
	stringstream ss;
	string s;
	ss << postfix;
	while (ss >> s) {
		while (ss.peek() == ' ') ss.ignore();
		if (s == "+" || s == "-" || s == "*" || s == "/") {
			v = st.top(), st.pop(), u = st.top(), st.pop();
			if(s == "+") st.push(u+v);
			else if (s == "-") st.push(u-v);
			else if (s == "*") st.push(u*v);
			else if (s == "/") st.push(u/v);
		}
		else st.push(atoi(s.c_str()));
	}
	return st.top();
}

int main() {
	string s;
	while (getline(cin, s)) cout << calculate(infix2postfix(s)) << endl;
}