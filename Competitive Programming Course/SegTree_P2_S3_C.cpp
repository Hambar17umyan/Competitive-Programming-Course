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

ll lazOp(ll a, ll b) {
	return a + b;
}

ll queryOp(ll a, ll b) {
	return max(a, b);
}

void push(int pos) {
	if (!tree[pos].isModified)
		return;

	tree[pos].isModified = false;

	if (tree[pos * 2].isModified) {
		tree[pos * 2].lazy = lazOp(tree[pos * 2].lazy, tree[pos].lazy);
		tree[pos * 2].val = lazOp(tree[pos * 2].val, tree[pos].lazy);
	}
	else {
		tree[pos * 2].lazy = tree[pos].lazy;
		tree[pos * 2].isModified = true;
		tree[pos * 2].val += tree[pos].lazy;
	}

	if (tree[pos * 2 + 1].isModified) {
		tree[pos * 2 + 1].lazy = lazOp(tree[pos * 2 + 1].lazy, tree[pos].lazy);
		tree[pos * 2 + 1].val = lazOp(tree[pos * 2 + 1].val, tree[pos].lazy);
	}
	else {
		tree[pos * 2 + 1].lazy = tree[pos].lazy;
		tree[pos * 2 + 1].isModified = true;
		tree[pos * 2 + 1].val += tree[pos].lazy;
	}

	tree[pos].val = queryOp(tree[pos * 2].val, tree[pos * 2 + 1].val);
}

ll query(int l, int tl, int tr, int pos, ll val) {
	if (tr < l || tree[pos].val < val)
		return -1;

	if (tl == tr) {
		if (tl < l)
			return -1;
		if (tree[pos].val >= val)
			return tl;
		else
			return -1;
	}

	push(pos);
	int middle = (tl + tr) / 2;

	if (tree[pos * 2].val >= val) {
		ll left = query(l, tl, middle, pos * 2, val);
		if (left != -1) {
			return left;
		}
	}
	if(tree[pos * 2 + 1].val >= val) {
		ll right = query(l, middle + 1, tr, pos * 2 + 1, val);
		if (right != -1) {
			return right;
		}
	}

	return -1;
}

void update(int l, int r, int tl, int tr, int pos, int val) {
	if (l == tl && r == tr) {
		if (tree[pos].isModified) {
			tree[pos].lazy = lazOp(tree[pos].lazy, val);
			tree[pos].val = lazOp(tree[pos].val, val);
		}
		else {
			tree[pos].lazy = val;
			tree[pos].isModified = true;
			tree[pos].val += val;
		}

		return;
	}

	push(pos);

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
			cin >> val >> l;
			cout << query(l, 0, n - 1, 1, val) << "\n";
		}
	}

	return 0;
}