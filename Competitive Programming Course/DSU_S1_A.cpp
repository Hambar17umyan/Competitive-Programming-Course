#include <iostream>
#include <vector>
using namespace std;

const int N = 100000 + 5;

vector<int> l[N];
int p[N];
int sz[N];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
        l[i].push_back(i);
    }
}

int get_set(int u) {
    return p[u];
}

void union_sets(int u, int v) {
    u = p[u];
    v = p[v];

    if (u == v)
        return;

    if (sz[u] > sz[v])
        swap(u, v);

    for (int x : l[u]) {
        p[x] = v;
        l[v].push_back(x);
    }

    sz[v] += sz[u];
    l[u].clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    init(n);

    while (m--) {
        string op;
        int u, v;
        cin >> op >> u >> v;

        if (op == "union") {
            union_sets(u, v);
        }
        else {
            cout << (get_set(u) == get_set(v) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}