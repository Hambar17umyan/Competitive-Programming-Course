#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct Edge {
	int b;
	int e;
	ll weight;
	Edge(int b, int e, ll weight) {
		this->b = b;
		this->e = e;
		this->weight = weight;
	}

	Edge() {
		this->b = 0;
		this->e = 0;
		this->weight = 0;
	}

	bool operator < (const Edge& other) const {
		return weight < other.weight;
	}
};

const int N = 2e5 + 5;
Edge edges[N];

struct DSU {
	vector<int> p, sz;

	DSU(int n) {
		p.resize(n + 1);
		sz.assign(n + 1, 1);

		for (int i = 1; i <= n; i++)
			p[i] = i;
	}

	int get_set(int v) {
		if (p[v] != v)
			p[v] = get_set(p[v]);
		return p[v];
	}

	void union_sets(int a, int b) {
		a = get_set(a);
		b = get_set(b);

		if (a == b) return;

		if (sz[a] > sz[b])
			swap(a, b);

		p[a] = b;
		sz[b] += sz[a];
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	int b, e;
	ll weight;

	for (int i = 0; i < m; i++) {
		cin >> b >> e >> weight;
		edges[i] = Edge(b, e, weight);
	}

	DSU dsu(n);
	sort(edges, edges + m);

	ll res = 0;
	for (int i = 0; i < m; i++) {
		Edge edge = edges[i];
		if (dsu.get_set(edge.b) != dsu.get_set(edge.e)) {
			dsu.union_sets(edge.b, edge.e);
			res += edge.weight;
		}
	}

	cout << res << endl;
}