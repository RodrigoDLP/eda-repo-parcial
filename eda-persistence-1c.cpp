#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


template<typename data_type>
struct segmenttreepointers {
    struct stnode {
        data_type value;
        int l, r;
        std::shared_ptr<stnode> left, right;
        stnode(data_type value, int l, int r, std::shared_ptr<stnode> left, std::shared_ptr<stnode> right):
            value(value), l(l), r(r), left(left), right(right) {}
    };
    std::shared_ptr<stnode> root;
    std::vector<std::shared_ptr<stnode>> versions;

    segmenttreepointers(int n) {
        versions.clear();
        versions.emplace_back(std::make_shared<stnode>(data_type(), 0, n-1, nullptr, nullptr));
        vector<data_type> v(n, data_type());
        build(versions[0], v);
    }

    segmenttreepointers(const int l, const int r, const std::vector<data_type>& v) {
        versions.clear();
        versions.emplace_back(std::make_shared<stnode>(data_type(), l, r, nullptr, nullptr));
        build(versions[0], v);
    }
    void build(const std::shared_ptr<stnode>& root, const std::vector<data_type>& v) {
        if (root->l == root->r) {
            if (root->l-1 > v.size()) throw std::runtime_error(":'(");
            root->value = v[root->l-1]; return;
        }
        int mid = (root->l+root->r)/2;
        root->left = std::make_shared<stnode>(data_type(), root->l, mid, nullptr, nullptr);
        root->right = std::make_shared<stnode>(data_type(), mid+1, root->r, nullptr, nullptr);
        build(root->left, v);
        build(root->right, v);
    }
    void update(const int index, const data_type& value, const int version) {
        if (version >= versions.size()) throw std::runtime_error("Version number too big");
        auto newroot = std::make_shared<stnode>(data_type(), versions[version]->l, versions[version]->r, nullptr, nullptr);
        versions.emplace_back(newroot);
        update(index, value, versions[version], newroot);
    }

    void update(const int& index, const data_type& value, const std::shared_ptr<stnode>& lastnode, const std::shared_ptr<stnode>& curr) {
        if (curr->l == curr->r){curr->value = value; return;}
        const int mi = (curr->l + curr->r)/2;
        if (index <= mi) {
            curr->left = std::make_shared<stnode>(lastnode->left->value, curr->l, mi, nullptr, nullptr);
            curr->right = lastnode->right;
            update(index, value, lastnode->left, curr->left);
        } else {
            curr->left = lastnode->left;
            curr->right = std::make_shared<stnode>(lastnode->right->value, mi+1, curr->r, nullptr, nullptr);
            update(index, value, lastnode->right, curr->right);
        }
        curr->value = curr->left->value + curr->right->value;
    }

    data_type query(const int version, const int l, const int r) {
        if (version >= versions.size()) throw std::runtime_error("Version number too big in query");
        return query(l, r, versions[version]);
    }
    data_type query(const int& l, const int& r, const std::shared_ptr<stnode>& root) {
        if (l > r || root->l > r || root->r < l) return data_type(0);
        if (l <= root->l && r >= root->r) return root->value;
        return query(l, r, root->left) + query(l, r, root->right);
    }

    int get_current_version() {return (int)versions.size()-1;}
};

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
struct persistent_queue {
    vector<int> heads, tails, roots;
    PersistentSegmentTree<data_type> data;
    explicit persistent_queue(int max_cap): data(max_cap) {
        roots.emplace_back(data.get_current_version()); heads.emplace_back(0); tails.emplace_back(0);
    }
    void push(int version, data_type value) {
        data.update(roots[version], tails[version], value);
        roots.emplace_back(data.get_current_version());
        heads.emplace_back(heads[version]);
        tails.emplace_back(tails[version] + 1);
    }
    data_type pop(int version) {
        data_type res = data.query(roots[version], heads[version], heads[version]);
        roots.emplace_back(roots[version]);
        //data.update(roots[version], tails[version], data_type());
        heads.emplace_back(heads[version]+1);
        tails.emplace_back(tails[version]);
        return res;
    }

};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    persistent_queue<int> q(n+1);
    int temp1, temp2, temp3;
    for (int i=0; i<n; ++i) {
        cin >> temp1;
        if (temp1 == 1) {
            cin >> temp2 >> temp3;
            q.push(temp2, temp3);
        } else {
            cin >> temp2;
            cout << q.pop(temp2) << "\n";
        }
    }


}