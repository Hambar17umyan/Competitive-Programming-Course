#include <iostream>
using namespace std;

const int N = 2e5 + 5;
int p[N];
int sz[N];
int xp[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
		xp[i] = 0;
	}
}

int get_set(int a) {
	if (p[a] == a)
		return a;

	int current_parent = p[a];
	int leader = get_set(current_parent);

	if (current_parent != leader) {
		xp[a] += xp[current_parent];
	}

	p[a] = leader;
	return leader;
}

void add_exp(int a, int v) {
	int leader = get_set(a);
	xp[leader] += v;
}

void union_sets(int a, int b) {
	a = get_set(a);
	b = get_set(b);
	if (a == b)
		return;
	if (sz[a] > sz[b])
		swap(a, b);
	p[a] = b;
	sz[b] += sz[a];
	xp[a] -= xp[b];
}

int main() {
	int n, m;
	cin >> n >> m;

	init(n);

	string op;
	while (m--) {
		cin >> op;
		int a, b;
		cin >> a;
		if (op == "join")
		{
			cin >> b;
			union_sets(a, b);
		}
		else if (op == "add") {
			cin >> b;
			add_exp(a, b);
		}
		else {
			int root = get_set(a);
			int playerxp = xp[a];
			if (a != root) {
				playerxp += xp[root];
			}
			cout << playerxp << '\n';
		}
	}
}