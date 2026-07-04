#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Node {
	ll max;
	ll lazy;
};

Node tree[4 * N];

void push(int pos, int tl, int tr) {
	if (tree[pos].lazy == 0)
		return;

	tree[pos * 2].max += tree[pos].lazy;
	tree[pos * 2 + 1].max += tree[pos].lazy;

	tree[pos * 2].lazy += tree[pos].lazy;
	tree[pos * 2 + 1].lazy += tree[pos].lazy;

	tree[pos].lazy = 0;
}

void update(int l, int r, int tl, int tr, int pos, ll v) {
	if (l == tl && tr == r) {
		tree[pos].max += v;
		tree[pos].lazy += v;
		return;
	}

	push(pos, tl, tr);
	int middle = (tl + tr) / 2;

	if (r < middle + 1)
		update(l, r, tl, middle, pos * 2, v);
	else if (l > middle)
		update(l, r, middle + 1, tr, pos * 2 + 1, v);
	else {
		update(l, middle, tl, middle, pos * 2, v);
		update(middle + 1, r, middle + 1, tr, pos * 2 + 1, v);
	}

	tree[pos].max = max(tree[pos * 2].max, tree[pos * 2 + 1].max);
}

int query(int tl, int tr, int pos, ll k, int l, int r) {
	if (tr < l || tree[pos].max < k)
		return -1;

	if (tl == tr) {
		if (tree[pos].max >= k)
			return tl;
		else
			return -1;
	}

	int middle = (tl + tr) / 2;

	if (l > middle) {
		return query(middle + 1, tr, pos * 2 + 1, k - tree[pos].lazy, l, r);
	}

	if (tree[pos * 2].max + tree[pos].lazy < k)
		return query(middle + 1, tr, pos * 2 + 1, k - tree[pos].lazy, l, r);
	else
		return query(tl, middle, pos * 2, k - tree[pos].lazy, l, r);
}

int main() {
	int n, m;
	cin >> n >> m;

	while (m--) {
		short op;
		cin >> op;

		if (op == 1) {
			int l, r;
			ll v;
			cin >> l >> r >> v;
			update(l, r - 1, 0, n - 1, 1, v);
		}
		else {
			ll x;
			int l;
			cin >> x >> l;
			cout << query(0, n - 1, 1, x, l, n - 1) << endl;
		}
	}

	return 0;
}