#include <bits/stdc++.h>
using namespace std;
// 1-indexed
// <function, segment tree node, init>
template<typename OP, typename T, typename S>
class SegmentTree {
public:
    OP op;
    T neut;
    int n;
    vector<T> st;
    SegmentTree(OP op, int n, T val)
        : op(op), neut(val), st(4 * n + 5, neut), n(n) {}
    SegmentTree(OP op, T val, vector<S>& a)
        : SegmentTree(op, a.size() - 1, val) {  // 1-indexed
        build(1, 1, n, a);
    }
    int left(int i) {return i * 2;}
    int right(int i) {return i * 2 + 1;}
    void build(int i, int l, int r, vector<S>& a) {
        if (l == r) st[i] = a[l];
        else {
            int m = (l + r) / 2;
            build(left(i), l, m, a);
            build(right(i), m + 1, r, a);
            st[i] = op(st[left(i)], st[right(i)]);
        }
    }
    void update(int i, int l, int r, int p, T v) {
        if (l == r) st[i] = v;
        else {
            int m = (l + r) / 2;
            if (p <= m) update(left(i), l, m, p, v);
            else update(right(i), m + 1, r, p, v);
            st[i] = op(st[left(i)], st[right(i)]);
        }
    }
    T query(int i, int l, int r, int x, int y) {
        if (x <= l && r <= y) return st[i];
        else {
            int m = (l + r) / 2;
            T t = neut;
            if (x <= m) t = op(t, query(left(i), l, m, x, y));
            if (m + 1 <= y) t = op(t, query(right(i), m + 1, r, x, y));
            return t;
        }
    }
    void update(int p, T v) {update(1, 1, n, p, v);}
    T query(int l, int r) {return query(1, 1, n, l, r);}
};

struct Node {
    int id;
    int val;
    Node(): id(0), val(0) {}
    Node(int val, int id): val(val), id(id) {}
};

Node Min(const Node& a, const Node& b) {
    if (a.val < b.val) return a;
    else return b;
}

// Usage: SegmentTree<
//              function<Node(const Node&, const Node&)>,
//              Node, Node> 
//                  segm_tree_min(Min, Node(INT_MAX, 0), data);