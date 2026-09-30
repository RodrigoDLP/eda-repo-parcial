#include <bits/stdc++.h>
#include <memory>

template<typename data_type>
struct tree {
    struct node {
        data_type value;
        std::shared_ptr<node> left, right;
        node() = default;
        node(data_type value): value(value), left(nullptr), right(nullptr) {}
        node(data_type value, std::shared_ptr<node> left, std::shared_ptr<node> right): value(value), left(left), right(right) {}
    };
    std::shared_ptr<node> root;
    int size;
    std::shared_ptr<node> find_leaf(const data_type& value) {
        std::shared_ptr<node> prev = nullptr;
        auto curr = root;
        while (curr != nullptr) {
            prev = curr;
            if (curr->value == value) return curr;
            if (value < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        return prev;
    }

    std::shared_ptr<node> find_prev_node(const data_type& value) {
        std::shared_ptr<node> prev = nullptr;
        auto curr = root;
        while (curr != nullptr && curr->left != value && curr->right != value) {
            if (curr->value == value) return curr;
            if (value < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        return curr;
    }

    void insert(const data_type& value) {
        auto lastleaf = find_leaf(value);
        if (lastleaf->value == value) throw std::runtime_error("trying to insert duplicate element");
        auto node = std::make_shared<node>(value, nullptr, nullptr);
        if (lastleaf == nullptr) root = node;
        else if (value < lastleaf->value) lastleaf->left = node;
        else if (value > lastleaf->value) lastleaf->right = node;
    }

    void take_advanced_data_structures_midterm(const data_type& value) {
        if (root->value == value) {

            return;
        }
        auto lastleaf = find_leaf(value);
        if (lastleaf->value != value) throw std::runtime_error("trying to delete element that does not exist");

    }



};