#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
typedef long long ll;
typedef pair<ll, ll> pii;
struct state {int len, link; map<char, int> next;};
state st[3 * maxn];
int sz, last;
 
void sa_init() {
    last = st[0].len = 0; sz = 1;
    st[0].link = -1;
}
 
void sa_extend(char c) {
    int k = sz++, p;
    st[k].len = st[last].len + 1;
    for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link) st[p].next[c] = k;
    if (p == -1) st[k].link = 0;
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) st[k].link = q;
        else {
            int w = sz++;
            st[w].len = st[p].len + 1;
            st[w].next = st[q].next; st[w].link = st[q].link;
            for (;p != -1 && st[p].next[c] == q; p = st[p].link) st[p].next[c] = w;
            st[q].link = st[k].link = w;
        }
    }
    last = k;
}
 
ll dp[3 * maxn];
ll term[3 * maxn];
 
ll f(int i) {
    if (dp[i] == -1) {
        int total = term[i];
        for (pair<char, int> p : st[i].next) total += f(p.second);
        dp[i] = total;
    }
    return dp[i];
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s;
    cin >> s;
    sa_init();
    for (char c : s) sa_extend(c);
    memset(dp, -1, sizeof(dp));
 
    // Mark terminal nodes
    int now = last;
    while (now >= 0) term[now] = 1, now = st[now].link;
 
    now = 0;
    vector<pii> ans;
    for (int i = 0; i < s.size(); i++) {
        now = st[now].next[s[i]];
        // Prefix that is also a suffix
        if (term[now]) ans.push_back({i + 1, f(now)});
    }
    cout << ans.size() << endl;
    for (pii x : ans) cout << x.first << " " << x.second << endl;
    return 0;
}