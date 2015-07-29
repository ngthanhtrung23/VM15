#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#define MAXN 100005
using namespace std;

/*
Optimal ( O(N log N) ) solution:
Start from
	DP[i] = max_{j < i} DP[j] + sum_{k in [j + 1, i - 1]} v[k] - (t[i] - t[k]) * d[k]
*/

long long INF = 1LL << 62;

struct pizza {
	long long timeArrival, value, decay;

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

struct point {
	long long x, y;

	point(long long _x, long long _y) : x(_x), y(_y) {};

	long long evaluate(long long t) {
		return x * t + y;
	}
};

double crossProduct(point A, point B, point C) {
	long long ax = B.x - A.x;
	long long ay = B.y - A.y;
	long long bx = C.x - B.x;
	long long by = C.y - B.y;
	double product = 1.0 * ax * by - 1.0 * ay * bx;
	return product;
}

struct convexHull {
	vector<struct point> pts;

	convexHull() {
		pts.clear();
	}

	void add(struct point p) {
		while (pts.size() > 1 && crossProduct(pts[pts.size() - 2], pts[pts.size() - 1], p) >= 0) {
			pts.pop_back();
		}
		pts.push_back(p);
	}

	long long get(long long t) {
		int low = 0, high = pts.size() - 1;
		long long maxValue = -INF;

		while (high - low > 5) {
			int m1 = (low + low + high)/3;
			int m2 = (low + high + high)/3;
			long long f1 = pts[m1].evaluate(t);
			long long f2 = pts[m2].evaluate(t);

			if (f1 > f2) {
				maxValue = max(maxValue, f1);
				high = m2 - 1;
			}
			else {
				maxValue = max(maxValue, f2);
				low = m1 + 1;
			}
		}

		for (int i = low; i <= high; i++) {
			maxValue = max(maxValue, pts[i].evaluate(t));
		}

		return maxValue;
	}
};

int N, B;
pizza P[MAXN];
long long dp[MAXN], sa[MAXN], sb[MAXN], sbb[MAXN];

struct point makePoint(int id) {
	// Only call this after dp[id] has been evaluated
	return point(sb[id], dp[id] - sa[id] - sbb[id]);
}

int main() {
	scanf("%d %d", &N, &B);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &P[i].timeArrival, &P[i].value, &P[i].decay);
	}
	sort(P + 1, P + N + 1);

	sa[0] = 0;
	for (int i = 1; i <= N; i++) {
		sa[i] = sa[i - 1] + P[i].value;
	}
	sb[0] = 0;
	for (int i = 1; i <= N; i++) {
		sb[i] = sb[i - 1] + P[i].decay;
	}
	sbb[0] = 0;
	for (int i = 1; i <= N; i++) {
		sbb[i] = sbb[i - 1] + 1LL * P[i].decay * P[i].timeArrival;
	}

	convexHull hull = convexHull();
	dp[0] = 0;
	hull.add(makePoint(0));

	for (int i = 1; i <= N; i++) {
		dp[i] = hull.get(P[i].timeArrival) - B + sa[i] - 1LL * P[i].timeArrival * sb[i] + sbb[i];
		hull.add(makePoint(i));
	}

	printf("%lld\n", dp[N]);
	return 0;
}
