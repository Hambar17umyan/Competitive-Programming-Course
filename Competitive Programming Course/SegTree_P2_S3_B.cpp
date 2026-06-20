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
    if (!tree[pos].lazy || tl == tr) 
        return;

    int mid = (tl + tr) / 2;

    tree[pos * 2].sum = (mid - tl + 1) - tree[pos * 2].sum;
    tree[pos * 2 + 1].sum = (tr - mid) - tree[pos * 2 + 1].sum;

    tree[pos * 2].lazy ^= 1;
    tree[pos * 2 + 1].lazy ^= 1;

    tree[pos].lazy = false;
}

void update(int l, int r, int tl, int tr, int pos) {
    if (l <= tl && tr <= r) {
        tree[pos].sum = (tr - tl + 1) - tree[pos].sum;
        tree[pos].lazy ^= 1;
        return;
    }

    push(pos, tl, tr);
    int mid = (tl + tr) / 2;

    if (l <= mid) 
        update(l, r, tl, mid, pos * 2);

    if (r > mid) 
        update(l, r, mid + 1, tr, pos * 2 + 1);

    tree[pos].sum = tree[pos * 2].sum + tree[pos * 2 + 1].sum;
}

int find_kth(int tl, int tr, int pos, ll k) {
    if (tl == tr) 
        return tl;

    push(pos, tl, tr);
    int middle = (tl + tr) / 2;

    ll left = tree[pos * 2].sum;

    if (k < left) {
        return find_kth(tl, middle, pos * 2, k);
    }
    else {
        return find_kth(middle + 1, tr, pos * 2 + 1, k - left);
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
            cout << find_kth(0, n - 1, 1, k) << endl;
        }
    }

    return 0;
}