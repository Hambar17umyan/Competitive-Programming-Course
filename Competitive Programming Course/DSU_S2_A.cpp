#include <iostream>
using namespace std;

const int N = 1e6 + 5;
int p[N], sz[N];

void init(int n) {
	for (int i = 1; i <= n; i++)
		p[i] = i;
}

int get_set(int x) {
	if (x == p[x])
		return x;
	p[x] = get_set(p[x]);

	return p[x];
}


void union_element_to_right(int x) {
	// We can be sure that x is the leader of x

	// We find the leftmost element that did not leave.
	// It is the same as finding the rightmost element in the set of x + 1
	int y = get_set(x + 1);
	p[x] = y;
}

int main() {
	int n, m;
	cin >> n >> m;
	init(n);

	bool last_left = false;
	while (m--) {
		char op;
		int x;
		cin >> op >> x;
		if (op == '-') {
			if (x == n) {
				last_left = true;
			}
			else {
				union_element_to_right(x);
			}
		}
		else {
			int right = get_set(x);
			if (right == n && last_left)
				right = -1;

			cout << right << endl;
		}
	}
}