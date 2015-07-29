/*
	A greedy solution: start with empty set, each time greedily choose the best solution
*/

#include <bits/stdc++.h>
#define MAXN 205
using namespace std;

int N, M;
vector<int> adj[MAXN];
int chosen[MAXN], bestSolution = 0, currentValue = 0;
vector<int> bestSet;

int evaluate(int value, int u) {
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (chosen[v]) {
			value--;
		}
		else {
			value++;
		}
	}
	return value;
}

bool update(int value, int u) {
	// Set the next chosen value to be u
	// u is not in the chosen list
	int tmp = evaluate(value, u);
	if (tmp <= bestSolution) {
		return false;
	}
	bestSolution = tmp;
	bestSet.clear();
	for (int i = 1; i <= N; i++) {
		if (chosen[i]) {
			bestSet.push_back(i);
		}
	}
	bestSet.push_back(u);
	return true;
}

void DFS(int u) {
	chosen[u] = true;
	int nextCandidate = -1;

	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!chosen[v]) {
			if (update(currentValue, v)) {
				nextCandidate = v;
			}
		}
	}

	if (nextCandidate > 0) {
		currentValue = bestSolution;
		DFS(nextCandidate);
	}
	chosen[u] = false;
}

int main() {
    srand(time(NULL));
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int startVertex = 1;
	for (int i = 1; i <= N; i++) {
		if (update(0, i)) {
			startVertex = i;
		}
	}
	currentValue = bestSolution;
	DFS(startVertex);

	printf("%d\n", bestSolution);
	printf("%d\n", (int) bestSet.size());
	for (int i = 0; i < bestSet.size(); i++) {
		printf("%d", bestSet[i]);
		if (i == bestSet.size() - 1) {
			printf("\n");
		}
		else {
			printf(" ");
		}
	}
	return 0;
}
