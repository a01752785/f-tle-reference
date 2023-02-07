#include <bits/stdc++.h>
using namespace std;
#define SZ(a) int(a.size())
#define mod 1000000007
typedef long long ll;
typedef vector<vector<ll>> Matrix;

Matrix ones(int n) {
    Matrix r(n, vector<ll>(n));
    for (int i = 0; i < n; i++) r[i][i] = 1;
    return r;
}

Matrix operator*(Matrix& a, Matrix& b) {
    int n = SZ(a), m = SZ(b[0]), z = SZ(a[0]);
    Matrix r(n, vector<ll>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < z; k++)
                r[i][j] += a[i][k] * b[k][j], r[i][j] %= mod;
    return r;
}

Matrix binary_exp(Matrix b, ll k) {
    Matrix r = ones(SZ(b));
    while (k) {
        if (k&1LL) r = r * b;
        b = b * b;
        k /= 2;
    }
    return r;
}
