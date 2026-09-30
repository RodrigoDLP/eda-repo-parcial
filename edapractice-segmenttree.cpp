#include <bits/stdc++.h>
#include <memory>

//1 indexed
template<typename data_type, size_t sz>
struct segment_tree {
    std::vector<data_type> elements;
    segment_tree() {elements.resize(sz*4, data_type());}
    segment_tree(const std::vector<data_type>& v) {elements.resize(sz*4, data_type()); build(v);}
    void build(const std::vector<data_type>& v) {
        for (int i=0; i<v.size(); ++i) {elements[sz+i] = v[i];}
        for (int i=sz-1; i>=0; --i) {elements[i] = v[i*2]+v[i*2+1];}
    }
    void update(const size_t& index, const data_type& value) {
        elements[sz+index] = value;
        for (int i=(sz+index)/2; i>=1; i/=2) {elements[i] = elements[i*2]+elements[i*2+1];}
    }
    data_type query(size_t l, size_t r) {
        data_type output = data_type();
        //implementación breve de GeeksforGeeks
        for (l+=sz, r+=sz; l<r; l=l/2, r=r/2) {
            if (l%2==1) output += elements[l++];
            if (r%2==1) output += elements[--r];
        } return output;
    }
};

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


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, a, b, c; std::cin >> n;
    std::vector<int> v(n); for (int i=0; i<n; ++i) std::cin >> v[i];
    segmenttreepointers tree(1, n, v);
    int m; std::cin >> m;
    for (int i=0; i<m; ++i) {
        std::string input; std::cin >> input;
        if (input[0] == 'c') {
            std::cin >> a >> b >> c;
            tree.update(b, c, a-1);
        } else if (input[0] == 'g') {
            std::cin >> a >> b;
            std::cout << tree.query(a-1, b, b) << "\n";
        } else throw std::runtime_error(":(");
    }
    return 0;
}