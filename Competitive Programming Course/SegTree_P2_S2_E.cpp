#include <iostream>
typedef long long ll;
using namespace std;

const ll N = 1e5 + 5;
ll arr[N];
pair<ll, ll> tree[N * 4];
bool modified[4 * N];

ll operate(ll node, ll value) {
	return value;
}

ll seg_func(ll a, ll b) {
	return min(a, b);
}

ll find_res(ll l, ll r, ll tl, ll tr, ll pos) {
	if (l == tl && r == tr) {
		return tree[pos].first;
	}

	ll middle = (tl + tr) / 2;
	if (r <= middle) {
		if (modified[pos])
			return operate(find_res(l, r, tl, middle, pos * 2), tree[pos].second);
		else
			return find_res(l, r, tl, middle, pos * 2);
	}

	if (l > middle) {
		if (modified[pos])
			return operate(find_res(l, r, middle + 1, tr, pos * 2 + 1), tree[pos].second);
		else
			return find_res(l, r, middle + 1, tr, pos * 2 + 1);
	}

	if (modified[pos])
		return seg_func(
			operate(find_res(l, middle, tl, middle, pos * 2), tree[pos].second),
			operate(find_res(middle + 1, r, middle + 1, tr, pos * 2 + 1), tree[pos].second)
		);
	else
		return seg_func(
			find_res(l, middle, tl, middle, pos * 2),
			find_res(middle + 1, r, middle + 1, tr, pos * 2 + 1)
		);
}

void update(ll l, ll r, ll tl, ll tr, ll pos, ll k) {
	if (l == tl && r == tr) {
		if (modified[pos])
			tree[pos].second = operate(tree[pos].second, k);
		else
			tree[pos].second = k;

		tree[pos].first = operate(tree[pos].first, k);

		modified[pos] = true;
		return;
	}

	if (modified[pos]) {
		if (modified[pos * 2]) {
			tree[pos * 2].second = operate(tree[pos * 2].second, tree[pos].second);
		}
		else {
			tree[pos * 2].second = tree[pos].second;
		}

		tree[pos * 2].first = operate(tree[pos * 2].first, tree[pos].second);
		modified[pos * 2] = true;

		if (modified[pos * 2 + 1]) {
			tree[pos * 2 + 1].second = operate(tree[pos * 2 + 1].second, tree[pos].second);
		}
		else {
			tree[pos * 2 + 1].second = tree[pos].second;
		}

		tree[pos * 2 + 1].first = operate(tree[pos * 2 + 1].first, tree[pos].second);
		modified[pos * 2 + 1] = true;

		modified[pos] = false;
	}

	ll middle = (tl + tr) / 2;
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

	if (modified[pos])
		tree[pos].first = operate(seg_func(tree[pos * 2].first, tree[pos * 2 + 1].first), tree[pos].second);
	else
		tree[pos].first = seg_func(tree[pos * 2].first, tree[pos * 2 + 1].first), tree[pos].second;
}

int main() {
	ll op;
	ll n, m, l, r, k;
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
			cout << find_res(l, r, 0, n - 1, 1) << endl;
		}
	}

	return 0;
}