#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<uint64_t> H;

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


int LASTRETURNEDINDEX = -1;


template<typename data_type>
struct PersistentMinimumQuerySegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentMinimumQuerySegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentMinimumQuerySegmentTree(int l, int r, vector<data_type> &a) {
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
            //curr -> data = value;
            curr->data = last->data ^ H[pos]; //TODO CHANGE
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
        data_type leftdata = curr->left->data, rightdata = curr->right->data;
        //TODO MAIN CHANGE
        curr->data = leftdata ^ rightdata;
        //if (leftdata == data_type() && rightdata == data_type()) curr->data = data_type();
        //else if (leftdata > data_type() && rightdata > data_type()) curr->data = data_type(2);
        //else curr->data = data_type(1);
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) {LASTRETURNEDINDEX = root->l; return root -> data;}
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

    int range_minimum_query(SegmentTreeNode* lastverminusone, SegmentTreeNode* currver) {
        //if (lastver->l == lastver->r) {cout << "INTERNAL QUERY ENDED. NODE=" << lastver->l << " VALUE=" << abs(currver->data - lastver->data) << "\n"; return abs(currver->data - lastver->data);}

        //if (abs(currver->left->data - lastver->left->data) > 0) return range_minimum_query(lastver->left, currver->left);
        //cout << "going right, l=" << lastver->l << " r=" << lastver->r << "\n";
        //return range_minimum_query(lastver->right, currver->right);
        if ((currver->data ^ lastverminusone->data) == 0) return -1;
        if (lastverminusone->l == lastverminusone->r) return lastverminusone->l;
        uint64_t left_xor = currver->left->data ^ lastverminusone->left->data;
        if (left_xor != 0) return range_minimum_query(lastverminusone->left,currver->left);
        return range_minimum_query(lastverminusone->right,currver->right);
    }

    int range_minimum_query(int lastverminusone, int currver) {
        return range_minimum_query(version_roots[lastverminusone],version_roots[currver]);
    }



    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};


int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; ++i) cin >> v[i];
    vector<int> compressor(v.begin(), v.end());
    sort(compressor.begin(), compressor.end());
    compressor.erase(unique(compressor.begin(), compressor.end()), compressor.end());
    for (int i=0; i<n; ++i) v[i] = lower_bound(compressor.begin(), compressor.end(), v[i]) - compressor.begin();
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    H.resize(compressor.size());
    for (auto &x : H) x = rng(); //rng and xorhash part was clearly ai suggested
    PersistentMinimumQuerySegmentTree<uint64_t> tree(compressor.size());
    /*unordered_map<int, int> currmap;
    for (int i=0; i<n; ++i) {
        if (!currmap.count(v[i])) currmap[v[i]] = 1; else currmap[v[i]]++;
        //cout << "for v[i] = " << v[i] << " currmap[v[i]]=" << currmap[v[i]] << "\n";
        if (currmap[v[i]] % 2 == 0) {tree.update(i, v[i], 0);}
        else tree.update(i, v[i], v[i]+1);
        //cout << "value of tree node in currv: " << tree.query(i+1, v[i], v[i]) << "\n";
    }*/
    for (int i=0; i<n; ++i) tree.update(i, v[i], 0);
    /*for (int v = 0; v <= n; ++v) {
        cout << "version " << v << ": ";
        for (int seat = 0; seat < compressor.size(); ++seat) {
            cout << tree.query(v, seat, seat) << " ";
        }
        cout << '\n';
    }*/
    int q; cin >> q; int ans = 0;
    for (int qi=0; qi<q; ++qi) {
        int a, b; cin >> a >> b;
        int l = a ^ ans, r = b ^ ans;
        //cout << "query for l=" << l << " r=" << r << " is ";
        int query_ans = tree.range_minimum_query(l-1, r);
        ans = query_ans == -1 ? 0 : compressor[query_ans];
        //ans = compressor[tree.range_minimum_query(l-1, r)];
        cout << ans << "\n";

    }
}