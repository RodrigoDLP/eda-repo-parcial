#include <bits/stdc++.h>
#include <memory>
#include <functional>
//falta: union de 2 bsts en O(n)
template<typename data_type>
struct bbst {
    struct bbstnode {
        data_type value; std::shared_ptr<bbstnode> left, right; size_t lssz, height, sz;
        bbstnode(data_type value, std::shared_ptr<bbstnode> left, std::shared_ptr<bbstnode> right, size_t lssz, size_t height, size_t sz):
            value(value), left(left), right(right), lssz(lssz), height(height), sz(sz) {}
    };
    std::shared_ptr<bbstnode> root;

    void insert(const data_type& value) {
        if (root == nullptr) {root = std::make_shared<bbstnode>(value, nullptr, nullptr, 0, 0, 1); return;}
        std::shared_ptr<bbstnode>* node = root;
        std::stack<std::reference_wrapper<std::shared_ptr<bbstnode>>> sk;
        while (*node != nullptr) {
            if (value == (*node)->value) throw std::runtime_error("Value already exists in BBST");
            sk.push(std::ref(*node));
            if (value < (*node)->value) node = &(*node)->left;
            else node = &(*node)->right;
        }
        //if (value < sk.top().get()->value) sk.top().get()->left = std::make_shared<bbstnode>(value, nullptr, nullptr, 0, 0, 1);
        //else sk.top().get()->right = std::make_shared<bbstnode>(value, nullptr, nullptr, 0, 0, 1);
        *node = std::make_shared<bbstnode>(value, nullptr, nullptr, 0, 0, 1);
        while (!sk.empty()) {
            //update_attributes(sk.top().get());
            //if (sk.top()->value > value) ++sk.top()->lssz;
            //++sk.top()->sz;
            balance(sk.top().get());
            sk.pop();
        }
    }

    bool search(const data_type& value) {
        std::shared_ptr<bbstnode> node = root;
        while (node != nullptr) {
            if (value == node->value) return true;
            if (value < node->value) node = node->left;
            else node = node->right;
        } return false;
    }

    size_t index(const data_type& value) {
        std::shared_ptr<bbstnode> node = root;
        while (node != nullptr) {
            if (value == node->value) return node->lssz;
            if (value < node->value) node = node->left;
            else node = node->right;
        } return -1;
    }

    //asume altura 0 para hojas
    size_t height(const data_type& value) {
        std::shared_ptr<bbstnode> node = root;
        while (node != nullptr) {
            if (value == node->value) return node->height;
            if (value < node->value) node = node->left;
            else node = node->right;
        } return -1;
    }


    std::shared_ptr<bbstnode> successor(const data_type& value) {
        if (root == nullptr) throw std::runtime_error("Trying to find successor of empty BBST");
        std::shared_ptr<bbstnode> lastleft = nullptr;
        std::shared_ptr<bbstnode> node = root;
        while (node != nullptr && node->value != value) {
            if (value < node->value) {lastleft = node; node = node->left;}
            else node = node->right;
        }
        if (node == nullptr) throw std::runtime_error("Node queried to find successor does not exist in BBST");
        if (lastleft == nullptr && node->right == nullptr) return nullptr;
        node = (node->right == nullptr) ? lastleft : node->right;
        while (node->left != nullptr) node = node->left;
        return node;
    }

    std::shared_ptr<bbstnode> predecessor(const data_type& value) {
        if (root == nullptr) throw std::runtime_error("Trying to find successor of empty BBST");
        std::shared_ptr<bbstnode> lastright = nullptr;
        std::shared_ptr<bbstnode> node = root;
        while (node != nullptr && node->value != value) {
            if (value > node->value) {lastright = node; node = node->right;}
            else node = node->left;
        }
        if (node == nullptr) throw std::runtime_error("Node queried to find successor does not exist in BBST");
        if (lastright == nullptr && node->left == nullptr) return nullptr;
        node = (node->left == nullptr) ? lastright : node->left;
        while (node->right != nullptr) node = node->right;
        return node;
    }

    void remove(const data_type& value) {
        if (root == nullptr) throw std::runtime_error("Trying to delete node from empty BBST");
        if (root->value == value && !root->left && !root->right) {root = nullptr; return;}
        if (root->value == value && !root->right) {root = root->left; return;}
        if (root->value == value && !root->left) {root = root->right; return;}
        std::shared_ptr<bbstnode>* node = &root;
        std::stack<std::reference_wrapper<std::shared_ptr<bbstnode>>> sk;
        std::shared_ptr<bbstnode> original_node = nullptr;
        data_type elim_value = value;
        while (*node != nullptr && (*node)->value != value) {
            sk.push(std::ref(*node));
            if (value < (*node)->value) node = &(*node)->left;
            else node = &(*node)->right;
        }
        if (*node == nullptr) throw std::runtime_error("Node queried to delete does not exist in BBST");
        if ((*node)->left && (*node)->right) {
            original_node = *node;
            sk.push(std::ref(*node));
            node = &(*node)->right;
            while ((*node)->left != nullptr) {sk.push(std::ref(*node)); node = &(*node)->left;}
            elim_value = node->value;
        } //notar que node no está en el stack y que el suc/pred será una hoja o con un hijo, y si no tiene suc ya es hoja o con un hijo
        if (!(*node)->left && !(*node)->right) {
            //if (node->value < sk.top().get()->value) sk.top().get()->left = nullptr;
            //else sk.top().get()->right = nullptr;
            *node = nullptr;
        } else if (node->left) {
            //if (node->value < sk.top().get()->value) sk.top().get()->left = node->left;
            //else sk.top().get()->right = node->left;
            *node = (*node)->left;
        } else if (node->right) {
            //if (node->value < sk.top().get()->value) sk.top().get()->left = node->right;
            //else sk.top().get()->right = node->right;
            *node = (*node)->right;
        } else throw std::runtime_error("Apparently we have got into an impossible case on BBST deletion");
        while (!sk.empty()) {
            //update_height(sk.top().get());
            //if (sk.top()->value > elim_value) --sk.top()->lssz;
            //--sk.top()->sz;
            balance(sk.top().get());
            sk.pop();
        }
        if (original_node) original_node->value = elim_value;
    }

    int balancing_factor(std::shared_ptr<bbstnode> node) {
        if (node == nullptr) return 0;
        size_t height_left = node->left ? node->left->height : -1;
        size_t height_right = node->right ? node->right->height : -1;
        return height_left - height_right;
    }

    void update_attributes(std::shared_ptr<bbstnode> node) {
        if (node == nullptr) return;
        const int height_left = node->left ? node->left->height : -1;
        const int height_right = node->right ? node->right->height : -1;
        const size_t sz_left = node->left ? node->left->sz : 0;
        const size_t sz_right = node->right ? node->right->sz : 0;
        node->lssz = sz_left;
        node->sz = sz_left + sz_right + 1;
        node->height = std::max(height_left, height_right) + 1;
        //if (node->left == nullptr && node->right == nullptr) node->height = 0;
        //else if (node->left == nullptr) node->height = node->right->height + 1;
        //else if (node->right == nullptr) node->height = node->left->height + 1;
        //else node->height = std::max(node->left->height, node->right->height) + 1;
    }

    void balance(std::shared_ptr<bbstnode>& node) {
        if (node == nullptr) return;
        update_attributes(node);
        if (balancing_factor(node) >= 2) {
            if (balancing_factor(node->left) <= -1) rotate_left(node->left);
            rotate_right(node);
        }
        if (balancing_factor(node) <= -2) {
            if (balancing_factor(node->right) >= 1) rotate_right(node->right);
            rotate_left(node);
        }
        update_attributes(node);
    }

    void rotate_left(std::shared_ptr<bbstnode>& x) {
        auto z = x->right;
        x->right = z->left;
        z->left = x;
        update_attributes(x);
        update_attributes(z);
        x = z;
    }

    void rotate_right(std::shared_ptr<bbstnode>& y) {
        auto z = y->left;
        y->left = z->right;
        z->right = y;
        update_attributes(y);
        update_attributes(z);
        y = z;
    }

};
