#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Node {
	ll sum;
	ll suf;
	ll pref;
	ll seg;
	ll lazy;
	bool updated = false;
};

Node tree[4 * N];

void push(int pos, int tl, int tr) {
	if (!tree[pos].updated)
		return;

	int middle = (tl + tr) / 2;

	tree[pos * 2].sum = tree[pos].lazy * (middle - tl + 1);
	tree[pos * 2].lazy = tree[pos].lazy;
	tree[pos * 2].pref = max(0ll, tree[pos * 2].sum);
	tree[pos * 2].suf = max(0ll, tree[pos * 2].sum);
	tree[pos * 2].seg = max(0ll, tree[pos * 2].sum);
	tree[pos * 2].updated = true;

	tree[pos * 2 + 1].sum = tree[pos].lazy * (tr - middle);
	tree[pos * 2 + 1].lazy = tree[pos].lazy;
	tree[pos * 2 + 1].pref = max(0ll, tree[pos * 2 + 1].sum);
	tree[pos * 2 + 1].suf = max(0ll, tree[pos * 2 + 1].sum);
	tree[pos * 2 + 1].seg = max(0ll, tree[pos * 2 + 1].sum);
	tree[pos * 2 + 1].updated = true;

	tree[pos].updated = false;
}

void update(int l, int r, int tl, int tr, int pos, ll v) {
	if (l == tl && tr == r) {
		tree[pos].sum = v * (tr - tl + 1);
		tree[pos].lazy = v;
		tree[pos].pref = max(0ll, tree[pos].sum);
		tree[pos].suf = max(0ll, tree[pos].sum);
		tree[pos].seg = max(0ll, tree[pos].sum);
		tree[pos].updated = true;

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

	tree[pos].sum = tree[pos * 2].sum + tree[pos * 2 + 1].sum;
	tree[pos].pref = max(tree[pos * 2].pref, tree[pos * 2].sum + tree[pos * 2 + 1].pref);
	tree[pos].suf = max(tree[pos * 2 + 1].suf, tree[pos * 2 + 1].sum + tree[pos * 2].suf);
	tree[pos].seg = max(max(tree[pos * 2].seg, tree[pos * 2 + 1].seg), tree[pos * 2].suf + tree[pos * 2 + 1].pref);
}

int main() {
	int n, m;
	cin >> n >> m;

	while (m--) {
		ll l, r, v;
		cin >> l >> r >> v;
		r--;
		update(l, r, 0, n - 1, 1, v);
		cout << tree[1].seg << endl;
	}

	return 0;
}