#include <iostream>
typedef long long ll;
using namespace std;

const int N = 1e5 + 5;
ll arr[N];
pair<ll, ll> tree[N * 4];

ll operate(ll node, ll value) {
	return node | value;
}

ll seg_func(ll a, ll b) {
	return a & b;
}

ll find_and(int l, int r, int tl, int tr, int pos) {
	if (l == tl && r == tr) {
		return tree[pos].first;
	}

	int middle = (tl + tr) / 2;
	if (r <= middle) {
		return operate(tree[pos].second, find_and(l, r, tl, middle, pos * 2));
	}

	if (l > middle) {
		return operate(tree[pos].second, find_and(l, r, middle + 1, tr, pos * 2 + 1));
	}

	return seg_func(
		operate(tree[pos].second, find_and(l, middle, tl, middle, pos * 2)),
		operate(tree[pos].second, find_and(middle + 1, r, middle + 1, tr, pos * 2 + 1))
	);
}

void update(int l, int r, int tl, int tr, int pos, int k) {
	if (l == tl && r == tr) {
		tree[pos].second = operate(tree[pos].second, k);
		tree[pos].first = operate(tree[pos].first, k);
		return;
	}

	int middle = (tl + tr) / 2;
	if (r < middle + 1) {
		update(l, r, tl, middle, pos * 2, k);
	}
	else if (middle < l) {
		update(l, r, middle + 1, tr, pos * 2 + 1, k);
	}
	else {
		update(l, middle, tl, middle, pos * 2, k);
		update(middle + 1, r, middle + 1, tr, pos * 2 + 1, k);
	}

	tree[pos].first = operate(tree[pos].second, seg_func(tree[pos * 2].first, tree[pos * 2 + 1].first));
}

int main() {
	short op;
	int n, m, l, r, k;
	cin >> n >> m;
	while (m--) {
		cin >> op;
		if (op == 1) {
			cin >> l >> r >> k;
			r--;
			update(l, r, 0, n - 1, 1, k);
		}
		else {
			cin >> l >> r;
			r--;
			cout << find_and(l, r, 0, n - 1, 1) << endl;
		}
	}

	return 0;
}