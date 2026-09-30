#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct PersistentSegmentTree {
    struct SegmentTreeNode {
        T data;
        SegmentTreeNode* left, right;
        int l, r;
        SegmentTreeNode(T data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data),
            l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentSegmentTree(int l, int r) {
        version_roots.emplace_back(new SegmentTreeNode(T(), l, r, nullptr, nullptr));
        build(version_roots[0]);
    }
    void build(SegmentTreeNode* root) {
        if (root->l == root->r) {root->data = T(); return;}
        int mi = (root->l + root->r) / 2;
        root->left = new SegmentTreeNode(T(), root->l, mi, nullptr, nullptr);
        root->right = new SegmentTreeNode(T(), mi, root->r, nullptr, nullptr);
        build(root->left);
        build(root->right);
        root->data = root->left->data + root->right->data;
    }

    void update(int pos, T value, SegmentTreeNode* last, SegmentTreeNode* curr) {
        if (curr->l == curr->r) {curr->data = value; return;}
        int mi = (curr->l + curr->r)/2;
        if (pos <= mi) {
            curr->right = last->right;
            curr->left = new SegmentTreeNode(last->left->data, curr->l, mi, nullptr, nullptr);
            update(pos, value, last->left, curr->left);
        } else {

        }
        curr->data = curr->left->data + curr->right->data;
    }

    void update(int version, int pos, T value) {
        SegmentTreeNode* root = new SegmentTreeNode(T(), version_roots[0]->)
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
    }

};