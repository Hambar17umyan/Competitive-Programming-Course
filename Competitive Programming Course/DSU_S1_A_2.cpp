#include <iostream>
using namespace std;

const int N = 2e5 + 5;
int p[N];
int sz[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
	}
}

int get_set(int a) {
	if (p[a] != a)
		p[a] = get_set(p[a]);
	return p[a];
}

void union_sets(int a, int b) {
	a = get_set(a);
	b = get_set(b);
	if (sz[a] > sz[b])
		swap(a, b);
	p[a] = b;
	sz[b] += sz[a];
}

int main() {
	int n, m;
	cin >> n >> m;

	init(n);

	string op;
	while (m--) {
		cin >> op;
		int a, b;
		cin >> a >> b;
		if (op == "union")
			union_sets(a, b);
		else cout << ((get_set(a) == get_set(b)) ? "YES\n" : "NO\n");
	}
}