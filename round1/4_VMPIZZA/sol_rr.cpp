#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100100;

struct Hull {
    long long a[MN], b[MN];
    double x[MN];
    int head, tail;

    Hull(): head(1), tail(0) {}

    long long get(long long xQuery) {
        if (head > tail) return 0;
        while (head < tail && x[head + 1] <= xQuery) head++;
        x[head] = xQuery;
        return a[head] * xQuery + b[head];
    }

    void add(long long aNew, long long bNew) {
        double xNew = -1e18;
        while (head <= tail) {
            if (aNew == a[tail]) return;
            xNew = 1.0 * (b[tail] - bNew) / (aNew - a[tail]);
            if (head == tail || xNew >= x[tail]) break;
            tail--;
        }
        a[++tail] = aNew;
        b[tail] = bNew;
        x[tail] = xNew;
    }
};

struct Pizza {
    ll t, a, b;
} a[MN];

bool operator < (const Pizza& a, const Pizza& b) {
    return a.t < b.t;
}

ll f[MN], b, suma[MN], sumb[MN], sumtb[MN];
int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> b) {
        FOR(i,1,n) cin >> a[i].t >> a[i].a >> a[i].b;
        sort(a+1, a+n+1);

        FOR(i,1,n) {
            suma[i] = suma[i-1] + a[i].a;
            sumb[i] = sumb[i-1] + a[i].b;
            sumtb[i] = sumtb[i-1] + a[i].t * a[i].b;
        }

        Hull hull;
        hull.add(0, 0);
        FOR(i,1,n) {
            f[i] = -1000111000111000111LL;
            ll on_i = -b + suma[i] - a[i].t * sumb[i] + sumtb[i];

//            FOR(j,0,i) {
//                ll cur = f[j] - b
//                        + suma[i] - suma[j]
//                        - a[i].t * (sumb[i] - sumb[j])
//                        + sumtb[i] - sumtb[j];
//                f[i] = max(f[i], cur);
//            }
            f[i] = -hull.get(a[i].t) + on_i;
            hull.add(-sumb[i], - (f[i] - suma[i] - sumtb[i]));
        }
//        PR(f, n);
        cout << f[n] << endl;
    }
}
