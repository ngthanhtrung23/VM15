import math
import numpy as NP

N = 10**15
K = 100
MOD = math.factorial(15)

MAX_FIBO = 100111
fibo = [0] * MAX_FIBO
fibo[1] = 1
for i in xrange(2, MAX_FIBO):
    fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD


def matrix_pow_mod(mat, k):
    n = mat.shape[0]
    if k == 0:
        return NP.identity(n)
    if k == 1:
        return mat

    temp = matrix_pow_mod(mat, k / 2)
    temp = temp * temp % MOD
    if k % 2 == 1:
        temp = temp * mat % MOD

    return temp


def pow_mod(x, k):
    if k == 0:
        return 1
    if k == 1:
        return x % MOD

    temp = pow_mod(x, k / 2)
    temp = temp * temp % MOD
    if k % 2 == 1:
        temp = temp * x % MOD
    return temp


def F(n, x):
    res = 0
    for i in xrange(n+1):
        res = (res + fibo[i] * pow_mod(x, i)) % MOD
    return res


def G(n, x):
    if n <= 2:
        return F(n, x) + 1

    F1 = NP.matrix([[1, 0, 0], [0, 0, 1], [1 - x*x + MOD, x*x, x]]) % MOD
    Fn = matrix_pow_mod(F1, n - 2)
    V1 = NP.matrix([[1], [G(1, x)], [G(2, x)]]) % MOD
    res = Fn * V1 % MOD
    return res.item((2, 0))


res = 0
for x in xrange(1, 101):
    res += (G(N, x) - 1) % MOD
print "res =", res % MOD
print "MOD =", MOD
print "ans =", 252541322550
