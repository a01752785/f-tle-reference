#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    Node *left, *right;
    ll value;
    Node() : value(0), left(nullptr), right(nullptr) {}
    Node(ll value) : value(value), left(nullptr), right(nullptr) {}
    Node(Node* node) : value(node->value), left(node->left), right(node->right) {}
};

ll get_value(Node* node) {
    return node? node->value : 0;
}

void recompute(Node* node) {
    node->value = get_value(node->left) + get_value(node->right);
}

ll query(Node* node, int l, int r, int x, int y) {
    if (x <= l && r <= y) return get_value(node);
    else {
        int mid = (l + r) / 2;
        ll sum = 0;
        if (x <= mid)
            sum += query(node->left, l, mid, x, y);
        if (mid + 1 <= y)
            sum += query(node->right, mid + 1, r, x, y);
        return sum;
    }
}

Node* update(Node* node, int l, int r, int p, ll v) {
    if (l == r) {
        return new Node(get_value(node) + v);
    } else {
        Node* node_copy = node? new Node(node) : new Node();
        int mid = (l + r) / 2;
        if (p <= mid)
            node_copy->left = update(node_copy->left, l, mid, p, v);
        else
            node_copy->right = update(node_copy->right, mid + 1, r, p, v);
        recompute(node_copy);
        return node_copy;
    }
}