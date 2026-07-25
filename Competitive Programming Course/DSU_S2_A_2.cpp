#include <iostream>
using namespace std;

const int N = 1e6 + 5;
int p[N];
int sz[N];
int mx[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = mx[i] = i;
		sz[i] = 1;
	}
}

int get_set(int a) {
	if (p[a] != a)
	{
		p[a] = get_set(p[a]);
	}

	return p[a];
}

void union_sets(int a, int b) {
	a = get_set(a);
	b = get_set(b);
	if (a == b)
		return;
	if (sz[a] > sz[b])
		swap(a, b);
	p[a] = b;
	mx[b] = max(mx[b], mx[a]);
	sz[b] += sz[a];
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
				union_sets(x, x + 1);
			}
		}
		else {
			int right = mx[get_set(x)];
			if (right == n && last_left)
				right = -1;

			cout << right << endl;
		}
	}
}