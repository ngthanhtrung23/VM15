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
#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (S & TWO(X))

// Assert with message
#define ASSERT(b, mess) { \
    if (!(b)) { \
        cout << mess << endl; \
        assert((b));\
    } \
}
using namespace std;

void solve();

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    clock_t startTime = clock();

    solve();
    return 0;
}

const int MN = 1000111;
double s[MN], f[MN];
int sieve[MN];

void solve() {
    f[0] = 0;
    FOR(i,1,MN-1) f[i] = f[i-1] + 1.0 / (double) i;

    FOR(i,3,MN-1) {
        s[i] = 1.0 / i * f[i-1];
        if (i % 2 == 0) s[i] -= 1.0 / i / (i/2);
    }

    FOR(x,2,MN-1) if (!sieve[x]) {
        for(int y = x + x; y < MN; y += x) {
            s[y] -= s[x] * 1.0 / (y/x) / (y/x);
        }
    }

    FOR(i,2,MN-1) s[i] += s[i-1] + 0.5;

    int n;
    while (cin >> n) cout << s[n] << endl;
}
