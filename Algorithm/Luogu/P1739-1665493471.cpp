#include <bits/stdc++.h>

int main() {
	std::string s;
	std::getline(std::cin, s);
	std::stack<int> st;
	for (int i = 0; i < s.size(); i ++) {
		if (s[i] == '(') {
			st.push('(');
		} else if (s[i] == ')') {
			if (!st.empty() && st.top() == '(') {
				st.pop();
			} else {
				goto JUDGE;
			}
		}
	}
	if (st.empty()) {
		std::cout << "YES\n";
	} else {
		JUDGE:
		std::cout << "NO\n";
	}
}