#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 50005;

int p[N];
int sz[N];

struct Query {
    string op;
    int u, v;
};

void init(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
}

int get_set(int a) {
    if (p[a] != a)
        p[a] = get_set(p[a]);
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

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
    }

    init(n);
    vector<Query> queries(k);

    for (int i = 0; i < k; i++)
    {
        cin >> queries[i].op >> queries[i].u >> queries[i].v;
    }

    vector<string> res;
    for (int i = k - 1; i >= 0; i--) {
        if (queries[i].op == "ask") {
            if (get_set(queries[i].u) == get_set(queries[i].v))
                res.push_back("YES");
            else
                res.push_back("NO");
        }
        else {
            union_sets(queries[i].u, queries[i].v);
        }
    }

    reverse(res.begin(), res.end());

    for (string s : res)
        cout << s << '\n';

    return 0;
}