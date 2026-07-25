#include <iostream>
using namespace std;

const int N = 3e5 + 5;
int p[N];
int sz[N];

int mx1[N];
int sz1[N];
int p1[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
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
	sz[b] += sz[a];
}



void init1(int n) {
	for (int i = 1; i <= n; i++) {
		p1[i] = i;
		sz1[i] = 1;
		mx1[i] = i;
	}
}

int get_set1(int a) {
	if (p1[a] != a)
	{
		p1[a] = get_set1(p1[a]);
	}

	return p1[a];
}

int union_sets1(int a, int b) {
	a = get_set1(a);
	b = get_set1(b);
	if (a == b)
		return mx1[b];
	if (sz1[a] > sz1[b])
		swap(a, b);
	p1[a] = b;
	mx1[b] = max(mx1[b], mx1[a]);
	sz1[b] += sz1[a];
	return mx1[b];
}



int main() {
	int n, m;
	cin >> n >> m;

	init(n);
	init1(n);

	short op;
	while (m--) {
		cin >> op;
		int a, b;
		cin >> a >> b;
		if (op == 1)
		{
			union_sets(a, b);
		}
		else if (op == 2) {
			int left = a;
			while (left < b) {
				int mx = union_sets1(left, left + 1);
				union_sets(left, left + 1);
				left = mx;
			}
		}
		else if(op == 3) {
			cout << ((get_set(a) == get_set(b)) ? "YES\n" : "NO\n");
		}
	}
}