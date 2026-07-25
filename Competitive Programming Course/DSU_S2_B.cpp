#include <iostream>
using namespace std;

const int N = 3e5 + 5;
int p[2 * N];
int sz[2 * N];
int mx[2 * N];

void init(int n) {
	for (int i = 1; i <= 2 * n; i++) {
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
	cin >> n;
	init(n);
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		int pk = get_set(k);
		int res = mx[pk] % n;
		if (res == 0)
			res = n;

		cout << res << endl;

		k = res;

		union_sets(k, k + 1);
		if (k != n) {
			union_sets(k + n, k + n + 1);
		}
	}
}