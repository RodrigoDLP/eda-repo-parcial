#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long long ll;



template<typename data_type>
struct PersistentSegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentSegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentSegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data = value;
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = curr -> left -> data + curr -> right -> data;
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }
    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};

template<typename data_type>
struct PersistentMinSegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentMinSegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentMinSegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data = value;
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = min(curr -> left -> data, curr -> right -> data);
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }
    int get_current_version() {
        return (int)version_roots.size() - 1;
    }


    int descend_one(int k, SegmentTreeNode* ver) {
        if (k < ver->data) return -1;
        if (ver->l == ver->r) return ver->l;
        if (k >= ver->left->data) return descend_one(k, ver->left);
        return descend_one(k, ver->right);
    }

    int descend_one(int k, int version) {
        return descend_one(k, version_roots[version]);
    }
};





template<typename data_type>
struct PersistentFrequencySegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentFrequencySegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentFrequencySegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data += value; //cambio está aquí
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = curr -> left -> data + curr -> right -> data;
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }

    int kth(int k, SegmentTreeNode* lastver, SegmentTreeNode* currver) {
        if (lastver->l == lastver->r) return lastver->l;
        if (k <= currver->left->data - lastver->left->data) return kth(k, lastver->left, currver->left);
        return kth(k - (currver->left->data - lastver->left->data), lastver->right, currver->right);
    }

    int kth(int k, int lastver, int currver) {
        return kth(k, version_roots[lastver], version_roots[currver]);
    }



    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};





auto lambda = [](auto& a, auto& b){return get<1>(a) < get<1>(b);};
auto lambda2 = [](auto& a, auto& b){return get<1>(a) < b;};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, s, m; cin >> n >> s >> m;
    PersistentMinSegmentTree<int> tree(s);
    vector<tuple<int, int, int>> tickets;
    unordered_map<int, int> lastassignedseat;
    for (int i=0; i<m; ++i) {
        int ci, ai, bi; cin >> ci >> ai >> bi;
        tickets.emplace_back(ci, ai, bi);
    }
    stable_sort(tickets.begin(), tickets.end(), lambda);
    for (int i=0; i<m; ++i) {
        int seat0index = get<0>(tickets[i])-1;
        int newval = get<2>(tickets[i]);
        if (!lastassignedseat.count(seat0index) || lastassignedseat[seat0index] < newval) lastassignedseat[seat0index] = newval;
        tree.update(i, seat0index, lastassignedseat[seat0index]);
    }
    //for (int v = 0; v <= m; ++v) {
    //    cout << "version " << v << ": ";
    //    for (int seat = 0; seat < s; ++seat) {
    //        cout << tree.query(v, seat, seat) << " ";
    //    }
    //    cout << '\n';
    //}
    int q; cin >> q; int p = 0;
    for (int qi = 0; qi < q; ++qi) {
        int x, y; cin >> x >> y;
        int a = x+p, b = y+p;
        int v = lower_bound(tickets.begin(), tickets.end(), b, lambda2) - tickets.begin();
        p = tree.descend_one(a, v) + 1;
        cout << p << "\n";
    }




}
