#include <algorithm>
#include <cstdio>
#define MAXN 100005
using namespace std;

/*
Brute force ( O(N^2) ) solution:
DP[i] = max_{j < i} -B + DP[j] + sum_{k in [j + 1, i - 1]} v[k] - (t[i] - t[k]) * d[k]
*/

struct pizza {
	int timeArrival, value, decay;

	bool operator <(const pizza& other) const {
		if (timeArrival != other.timeArrival) {
			return timeArrival < other.timeArrival;
		}
		if (value != other.value) {
			return value < other.value;
		}
		return decay < other.decay;
	}
};


int N, B;
pizza P[MAXN];
long long dp[MAXN];
long long INF = 1LL << 62;

int main() {
	scanf("%d %d", &N, &B);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &P[i].timeArrival, &P[i].value, &P[i].decay);
	}
	sort(P + 1, P + N + 1);

	dp[0] = 0;
	for (int i = 1; i <= N; i++) {
		dp[i] = -INF;
		long long sum = 0;
		for (int j = i; j > 0; j--) {
			sum += P[j].value - 1LL * (P[i].timeArrival - P[j].timeArrival) * P[j].decay;
			dp[i] = max(dp[i], sum + dp[j - 1] - B);
		}
	}
	printf("%lld\n", dp[N]);
	return 0;
}