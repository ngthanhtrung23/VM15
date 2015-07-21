#include <algorithm>
#include <cstdio>
#include <vector>
#define MAXN 100005
using namespace std;

int N;
pair<int,int> info[MAXN];
vector<int> child[MAXN];
int counter = 0;
int start[MAXN], finish[MAXN];
int sum[8 * MAXN];

void DFS(int u) {
	start[u] = counter++;
	for (int i = 0; i < child[u].size(); i++) {
		DFS(child[u][i]);
	}
	finish[u] = counter++;
}

bool cmp(pair<int,int> A, pair<int,int> B) {
	if (A.first != B.first) {
		return A.first < B.first;
	}
	return start[A.second] < start[B.second];
}

int get(int i, int u, int v, int low, int high) {
	if (high < u || v < low) {
		return 0;
	}
	if (low <= u && v <= high) {
		return sum[i];
	}
	int mid = (u + v) >> 1;
	return get(2 * i, u, mid, low, high) + get(2 * i + 1, mid + 1, v, low, high);
}

int getSum(int low, int high) {
	return get(1, 0, counter - 1, low, high);
}

void add(int i, int u, int v, int node) {
	if (u == v) {
		sum[i]++;
		return;
	}
	int mid = (u + v) >> 1;
	if (node <= mid) {
		add(2 * i, u, mid, node);
	}
	else {
		add(2 * i + 1, mid + 1, v, node);
	}
	sum[i] = sum[2 * i] + sum[2 * i + 1];
}

void addSum(int node) {
	add(1, 0, counter - 1, node);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		if (i > 1) {
			int pred;
			scanf("%d", &pred);
			child[pred].push_back(i);
		}

		int salary;
		scanf("%d", &salary);
		info[i] = make_pair(salary, i);
	}
	DFS(1);
	sort(info + 1, info + N + 1, cmp);

	long long ans = 0;
	for (int i = 1; i <= N; i++) {
		int node = info[i].second;
		int subtreeCount = getSum(start[node], finish[node]);
		ans += 1LL * subtreeCount * (subtreeCount - 1)/2;
		addSum(start[node]);
	}
	printf("%lld\n", ans);
	return 0;
}
