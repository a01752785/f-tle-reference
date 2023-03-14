#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class MyString {
private:
    vector<ll> h;
    vector<ll> a_pow;
    ll a = 31;
    ll b = 1792834759;
    int n;
    void pre_hash() {
        a_pow[0] = a;
        for (int i = 1; i <= n; i++) {
            a_pow[i] = (a_pow[i - 1] * a) % b;
        }
        h[0] = s[0];
        for (int i = 1; i < n; i++) {
            h[i] = (h[i - 1] * a + s[i]) % b;
        }
    }
public:
    string s;
    MyString() {}
    MyString(string s1) {
        s = s1;
        n = s.size();
        h = vector<ll>(n + 10);
        a_pow = vector<ll>(n + 10);
        pre_hash();
    }
    ll get_hash(int l, int r) {
        if (l == 0) return h[r];
        ll result = (h[r] - (h[l - 1] * a_pow[r - l]) % b + b) % b;
        return result;
    }
};