#include <bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(int i=(a); i <= (b); ++i)
#define REP(i,a) for(int i=0; i < (a); ++i)
using namespace std;

const ll N = 1e15;
const int K = 100;
const ll MOD = 1307674368000LL;

const int MAX_FIBO = 100111;
ll fibo[MAX_FIBO + 11];

ll mult(ll a, ll b) {
    if (b == 0) return 0;
    if (b == 1) return a % MOD;
    if (a <= (ll) (1e18) / b) return a * b % MOD;

    ll mid = mult(a, b/2);
    mid = (mid + mid) % MOD;
    if (b & 1) return (mid + a) % MOD;
    else return mid;
}

struct Matrix {
    ll x[3][3];
} I, F1;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    REP(i,3) REP(j,3) {
        c.x[i][j] = 0;
        REP(k,3)
            c.x[i][j] = (c.x[i][j] + mult(a.x[i][k], b.x[k][j])) % MOD;
    }
    return c;
}

Matrix power(const Matrix& a, ll k) {
    if (k == 0) return I;
    if (k == 1) return F1;
    Matrix mid = power(a, k >> 1);
    mid = mid * mid;

    if (k & 1) return mid * a;
    else return mid;
}

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    ll mid = power(x, k >> 1);
    mid = mult(mid, mid);
    if (k & 1) return mult(mid, x);
    else return mid;
}

ll F(ll n, ll x) {
    ll res = 0;
    REP(i,n+1)
        res = (res + mult(fibo[i], power(x, i))) % MOD;
    return res;
}

ll G(ll n, ll x) {
    if (n <= 2) return (F(n, x) + 1) % MOD;

    memset(F1.x, 0, sizeof F1.x);
    F1.x[0][0] = 1;
    F1.x[1][2] = 1;
    F1.x[2][0] = (1 - mult(x, x) + MOD) % MOD;
    F1.x[2][1] = mult(x, x);
    F1.x[2][2] = x % MOD;

    Matrix Fn = power(F1, n-2);

    return (Fn.x[2][0]
        + mult(Fn.x[2][1], G(1, x))
        + mult(Fn.x[2][2], G(2, x))) % MOD;
}

int main() {
    fibo[1] = 1;
    FOR(i,2,MAX_FIBO) fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD;
    I.x[0][0] = I.x[1][1] = I.x[2][2] = 1;

    cout << N << endl;
    cout << F(7, 11) << endl;
    cout << G(7, 11) << endl;

    ll res = 0;
    REP(x,101) {
        res = (res + G(N, x) - 1 + MOD) % MOD;
    }
    cout << res << endl;
}
