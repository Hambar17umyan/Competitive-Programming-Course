#include <iostream>
using namespace std;

const int N = 3e5 + 5;
int p[N];
int sz[N];
int mn[N], mx[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = mx[i] = mn[i] = i;
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
	mn[b] = min(mn[b], mn[a]);
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
		cin >> a;
		if (op == "union")
		{
			cin >> b;
			union_sets(a, b);
		}
		else {
			a = get_set(a);
			cout << mn[a] << ' ' << mx[a] << ' ' << sz[a] << '\n';
		}
	}
}