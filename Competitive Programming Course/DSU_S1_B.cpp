#include <iostream>
#include <vector>
using namespace std;

const int N = 300000 + 5;

vector<int> l[N];
int p[N];
int sz[N];
int mn[N], mx[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
		mn[i] = i;
		mx[i] = i;
		l[i].push_back(i);
	}
}

int get_set(int u) {
	return p[u];
}

void union_sets(int u, int v) {
	u = p[u];
	v = p[v];

	if (u == v)
		return;

	if (sz[u] > sz[v])
		swap(u, v);

	for (int x : l[u]) {
		p[x] = v;
		l[v].push_back(x);
	}

	sz[v] += sz[u];
	mn[v] = min(mn[v], mn[u]);
	mx[v] = max(mx[v], mx[u]);
	l[u].clear();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	init(n);

	while (m--) {
		string op;
		int u, v;
		cin >> op >> u;

		if (op == "union") {
			cin >> v;
			union_sets(u, v);
		}
		else {
			int st = get_set(u);
			cout << mn[st] << ' ' << mx[st] << ' ' << sz[st] << '\n';
		}
	}

	return 0;
}