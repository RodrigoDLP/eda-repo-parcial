#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


template<typename data_type, typename build_type, typename index_type>
struct RangeTree {

    struct RangeTreeNode {
        data_type sum;
        index_type l, r;
        RangeTreeNode left, right;
    };
    RangeTreeNode* root;
    RangeTree(vector<build_type> &a) {root = build_range_tree_from_indices(index_type(0), index_type((int)a.size()-1), a);}

    RangeTreeNode* build_range_tree_from_indices(index_type l, index_type r, vector<build_type>& a) {
        if (l == r) {
            auto* node = new RangeTreeNode(a[l], l, r);
            return node;
        }
        index_type mi = (l + r) / 2;
        RangeTreeNode* left = build_range_tree_from_indices(l, mi, a);
        RangeTreeNode* right = build_range_tree_from_indices(mi+1, r, a);
        auto* node = new RangeTreeNode(left->sum + right->sum, l, r);
        node->left = left; node->right = right;
        return node;
    }

    data_type query(RangeTreeNode* root, index_type l, index_type r) {
        if (r < root->l || root->r < l) return data_type();
        if (l <= root->l && root->r <= r) return root->sum;
        int mi = (l+r)/2;
        return query(root->left, l, mi) + query(root->right, mi+1, r);
    }

    data_type query(index_type l, index_type r) {
        return query(root, l, r);
    }
    void print(RangeTreeNode* root) {
        if (root ->l == root->r) {cout << root->l << " " << root->r << " " << root->sum << "\n"; return;}
        print(root->l);
        print(root->r);
        cout << root->l << " " << root->r << " " << root->sum << "\n";
    }

    void print() {
        print(root;
    }


};





int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i=0; i<n; ++i) cin >> a[i];
    RangeTree<ll> Solver(a);
    while (q--) {
        int l, r; cin >> l >> r;
        --r;
        cout << Solver.query(l, r) << "\n";
    }
}