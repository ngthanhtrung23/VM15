#include <bits/stdc++.h>
using namespace std;

#define MATRIX_SIZE 3
#define MODL 1307674368000ll


typedef long long int64;

struct matrix {
    int64 mat[MATRIX_SIZE][MATRIX_SIZE];

    matrix() {
        memset(mat, 0, sizeof mat);
    }

    int64 *operator [](int index) {
        return mat[index];
    }
};


int64 mult(int64 a, int64 b) {
    if (b == 0) return 0;

    int64 ret = mult((a + a) % MODL, b / 2);
    if (b & 1) ret = (ret + a) % MODL;
    return ret;
}

matrix mult(matrix a, matrix b) {
    matrix c;
    for (int i = 0; i < MATRIX_SIZE; i++) 
        for (int j = 0; j < MATRIX_SIZE; j++) {
            c[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++)
                c[i][j] = (c[i][j] + mult(a[i][k], b[k][j])) % MODL;
        }
    return c;
}


template<typename T>
T power(T a, int64 n) {
    if (n == 1) return a;

    T ret = power(mult(a, a), n / 2);
    if (n & 1) ret = mult(ret, a);
    return ret;
}

// ---

int64 solve(int64 k, int64 n) {
    int64 ans = 0;
    for (int64 x = 0; x <= k; x++) {
        matrix mat;

        //        fi  fi+1  si+1
        // fi+1    0     1     0
        // fi+2  x^2     x     0
        // si+2  x^2     x     1

        mat[0][1] = 1;
        mat[1][0] = mult(x, x); mat[1][1] = x;
        mat[2][0] = mult(x, x); mat[2][1] = x; mat[2][2] = 1;

        if (n == 0);
        else if (n == 1) 
            ans += x;
        else {
            mat = power(mat, n - 1);
            ans = (ans + mult(mat[2][1], x) + mult(mat[2][2], x)) % MODL;
        }
    }
    return ans;
}

int64 brute_force(int64 k, int64 n) {
    int64 f[10010], fx[10010];
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2]) % MODL;

    int64 ans = 0;
    for (int x = 0; x <= k; x++) {
        fx[0] = 0;
        int64 xx = 1;
        for (int i = 1; i <= n; i++) {
            xx = mult(xx, x);
            fx[i] = (fx[i - 1] + mult(f[i], xx)) % MODL;
        }
        ans = (ans + fx[n]) % MODL;
    }
    return ans;
}

void test() {
    assert(solve(2, 3) == brute_force(2, 3));
    assert(solve(10, 100) == brute_force(10, 100));
    assert(solve(12, 110) == brute_force(12, 110));
    assert(solve(19, 1100) == brute_force(19, 1100));
    assert(solve(1000, 1100) == brute_force(1000, 1100));
}

int main() {

    // Input
    // cin >> k >> n;

    // Test
    test();

    // Output
    // cout << solve(k, n);

    return 0;
}

