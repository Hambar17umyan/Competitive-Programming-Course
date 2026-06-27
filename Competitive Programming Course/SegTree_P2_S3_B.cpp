#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Node {
	ll sum = 0;
	bool lazy = false;
};

Node tree[4 * N];

void push(int pos, int tl, int tr) {
	if (!tree[pos].lazy)
		return;

	int middle = (tl + tr) / 2;

	tree[pos * 2].sum = (middle - tl + 1) - tree[pos * 2].sum;
	tree[pos * 2 + 1].sum = (tr - middle) - tree[pos * 2 + 1].sum;

	tree[pos * 2].lazy ^= 1;
	tree[pos * 2 + 1].lazy ^= 1;

	tree[pos].lazy = false;
}

void update(int l, int r, int tl, int tr, int pos) {
	if (l == tl && tr == r) {
		tree[pos].sum = (tr - tl + 1) - tree[pos].sum;
		tree[pos].lazy ^= 1;
		return;
	}

	push(pos, tl, tr);
	int middle = (tl + tr) / 2;

	if (r < middle + 1)
		update(l, r, tl, middle, pos * 2);
	else if (l > middle)
		update(l, r, middle + 1, tr, pos * 2 + 1);
	else {
		update(l, middle, tl, middle, pos * 2);
		update(middle + 1, r, middle + 1, tr, pos * 2 + 1);
	}

	tree[pos].sum = tree[pos * 2].sum + tree[pos * 2 + 1].sum;
}

int find_kth(int tl, int tr, int pos, ll k, bool bl) {
	if (tl == tr)
		return tl;

	bl ^= tree[pos].lazy;
	int middle = (tl + tr) / 2;

	ll left = bl ? (middle - tl + 1) - tree[pos * 2].sum : tree[pos * 2].sum;

	if (k < left) {
		return find_kth(tl, middle, pos * 2, k, bl);
	}
	else {
		return find_kth(middle + 1, tr, pos * 2 + 1, k - left, bl);
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	while (m--) {
		short op;
		cin >> op;

		if (op == 1) {
			int l, r;
			cin >> l >> r;
			update(l, r - 1, 0, n - 1, 1);
		}
		else {
			ll k;
			cin >> k;
			cout << find_kth(0, n - 1, 1, k, 0) << endl;
		}
	}

	return 0;
}