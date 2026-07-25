#include <iostream>
using namespace std;

const int N = 2e5 + 5;
int p[N];
int sz[N];
int prev_boss_count[N];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
		prev_boss_count[i] = 0;
	}
}

struct QueryResult
{
	int boss_count = 0;
	int super_boss = 0;

	QueryResult(int a, int b)
	{
		boss_count = a;
		super_boss = b;
	}
};

QueryResult go_up(int a) {
	if (p[a] == a)
		return QueryResult(0, a);

	int current_parent = p[a];
	auto res = go_up(current_parent);
	int bosses_of_parent = res.boss_count;
	int leader = res.super_boss;

	p[a] = leader;
	auto ans = QueryResult(bosses_of_parent + 1 + prev_boss_count[a], leader);
	prev_boss_count[a] += bosses_of_parent;
	return ans;
}

void union_sets(int a, int b) {
	if (a == b)
		return;
	p[a] = b;
	sz[b] += sz[a];
}

int main() {
	int n, m;
	cin >> n >> m;

	init(n);

	short op;
	int a, b;
	while (m--) {
		cin >> op >> a;
		if (op == 1) {
			cin >> b;
			union_sets(a, b);
		}
		else {
			cout << go_up(a).boss_count << '\n';
		}
	}
}
