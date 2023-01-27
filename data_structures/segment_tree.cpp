#include <bits/stdc++.h>
using namespace std;
#define F function<T(const T&, const T&)>
// 1-indexed
// <segment tree node, init>
template<typename T, typename S>
struct SegmentTree {
    F f;
    T neut;
    int n;
    vector<T> st;
    SegmentTree(F f, T val, int n)
        : f(f), neut(val), st(4 * n + 5, neut), n(n) {}
    SegmentTree(F f, T val, vector<S>& a)
        : SegmentTree(f, val, a.size() - 1) {  // 1-indexed
        build(1, 1, n, a);
    }
    int left(int i) {return i * 2;}
    int right(int i) {return i * 2 + 1;}
    void build(int i, int l, int r, vector<S>& a) {
        if (l == r) st[i] = T(a[l]);
        else {
            int m = (l + r) / 2;
            build(left(i), l, m, a);
            build(right(i), m + 1, r, a);
            st[i] = f(st[left(i)], st[right(i)]);
        }
    }
    void update(int i, int l, int r, int p, T v) {
        if (l == r) st[i] = v;
        else {
            int m = (l + r) / 2;
            if (p <= m) update(left(i), l, m, p, v);
            else update(right(i), m + 1, r, p, v);
            st[i] = f(st[left(i)], st[right(i)]);
        }
    }
    T query(int i, int l, int r, int x, int y) {
        if (x <= l && r <= y) return st[i];
        else {
            int m = (l + r) / 2;
            T t = neut;
            if (x <= m) t = f(t, query(left(i), l, m, x, y));
            if (m + 1 <= y) t = f(t, query(right(i), m + 1, r, x, y));
            return t;
        }
    }
    void update(int p, T v) {update(1, 1, n, p, v);}
    T query(int l, int r) {return query(1, 1, n, l, r);}
};
// Usage: SegmentTree<Node, ll> st_min(Min, Node(LLONG_MAX), data);
