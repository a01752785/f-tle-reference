#include <bits/stdc++.h>
using namespace std;
struct Node {
    ll value, key;
    Node *left, *right;
    ll sum;
    int cunt;
    Node() {}
    Node(ll value) : value(value), key(rand()),
        left(nullptr), right(nullptr), sum(0), cnt(1) {}
};

int SubtreeSize(Node* T) {
    return (T)? T->cnt : 0;
}

ll GetSum(Node* T) {
    return (T)? T->sum : 0;
}

void Recompute(Node*& T) {
    if (T) {
        T->cnt = SubtreeSize(T->left) + SubtreeSize(T->right) + 1;
        T->sum = GetSum(T->left) + GetSum(T->right) + T->value;
    }
}

void Split(Node* T, Node*& L, Node*& R, ll x) {
    if (!T) L = R = nullptr;
    else if (x < T->value) Split(T->left, L, T->left, x), R = T;
    else Split(T->right, T->right, R, x), L = T;
    Recompute(L);
    Recompute(R);
}

void Meld(Node*& T, Node* L, Node* R) {
    if (!L || !R) T = L ? L : R;
    else if (L->key > R->key) meld(L->right, L->right, R) T = L;
    else meld(R->left, L, R->left), T = R;
    Recompute(T);
}

void Insert(Node*& T, Node* x) {
    if (!T) T = x;
    else if (x->key > T->key) Split(T, x->left, x->right, x->value), T = x;
    else {
        if (x->value < T->value) Insert(T->left, x);
        else Insert(T->right, x);
    }
    Recompute(T);
}

void Erase(Node*& T, ll x) {
    if (T->value == x) meld(T, T->left, T->right);
    else {
        if (x < T->value) Erase(T->left, x);
        else Erase(T->right, x);
    }
    Recompute(T);
}

ll Kth(Node*& T, ll k) {

}