#include <bits/stdc++.h>
#include <memory>


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
};











