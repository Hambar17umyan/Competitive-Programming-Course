#include <iostream>
using namespace std;
typedef long long ll;

struct Node {
	ll val = 0;
	ll lazy = 0;
	bool isModified = false;
};

const int N = 1e5 + 5;
Node tree[4 * N];

ll nonComOp(ll a, ll b) {
	return b;
}

ll queryOp(ll a, ll b) {
	return a + b;
}

void push(int pos, int tl, int tr) {
	if (!tree[pos].isModified || tl == tr)
		return;

	int middle = (tl + tr) / 2;

	int leftLen = middle - tl + 1;
	int rightLen = tr - middle;

	tree[pos * 2].lazy = tree[pos].lazy;
	tree[pos * 2].isModified = true;
	tree[pos * 2].val = tree[pos].lazy * leftLen;

	tree[pos * 2 + 1].lazy = tree[pos].lazy;
	tree[pos * 2 + 1].isModified = true;
	tree[pos * 2 + 1].val = tree[pos].lazy * rightLen;

	tree[pos].isModified = false;
}

ll query(int l, int r, int tl, int tr, int pos) {
	if (l == tl && r == tr) {
		return tree[pos].val;
	}

	push(pos, tl, tr);

	int middle = (tl + tr) / 2;

	if (r < middle + 1) {
		return query(l, r, tl, middle, pos * 2);
	}
	else if (l > middle) {
		return query(l, r, middle + 1, tr, pos * 2 + 1);
	}
	else {
		return queryOp(query(l, middle, tl, middle, pos * 2), query(middle + 1, r, middle + 1, tr, pos * 2 + 1));
	}
}

void update(int l, int r, int tl, int tr, int pos, int val) {
	if (l == tl && r == tr) {
		tree[pos].lazy = val;
		tree[pos].isModified = true;
		tree[pos].val = 1LL * (tr - tl + 1) * val;
		return;
	}

	push(pos, tl, tr);

	int middle = (tl + tr) / 2;
	if (r < middle + 1) {
		update(l, r, tl, middle, pos * 2, val);
	}
	else if (l > middle) {
		update(l, r, middle + 1, tr, pos * 2 + 1, val);
	}
	else {
		update(l, middle, tl, middle, pos * 2, val);
		update(middle + 1, r, middle + 1, tr, pos * 2 + 1, val);
	}

	tree[pos].val = queryOp(tree[pos * 2].val, tree[pos * 2 + 1].val);
}

int main() {
	int n, m;
	cin >> n >> m;
	while (m--) {
		short op;
		int l, r;
		ll val;
		cin >> op;
		if (op == 1) {
			cin >> l >> r >> val;
			r--;
			update(l, r, 0, n - 1, 1, val);
		}
		else {
			cin >> l >> r;
			r--;
			cout << query(l, r, 0, n - 1, 1) << "\n";
		}
	}

	return 0;
}