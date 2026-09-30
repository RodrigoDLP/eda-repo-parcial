#include <bits/stdc++.h>
#include <memory>

template<typename data_type>
struct persistent_stack {
    struct persistent_stack_node {
        data_type value;
        std::shared_ptr<persistent_stack_node> next;
        persistent_stack_node(data_type value, std::shared_ptr<persistent_stack_node> next): value(value), next(next) {}
    };

    std::vector<std::shared_ptr<persistent_stack_node>> root;
    std::vector<int> sizev;
    persistent_stack() = default;

    void persistent_push(const data_type& value) {
        std::shared_ptr<persistent_stack_node> next = root.empty() ? nullptr : root[root.size()-1];
        auto node = std::make_shared<persistent_stack_node>(value, next);
        root.push_back(node);
        if (sizev.empty()) sizev.push_back(1);
        else sizev.push_back(sizev[sizev.size()-1]+1);
    }

    data_type persistent_pop() {
        if (root.empty() || root[root.size()-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        root.push_back(root[root.size()-1]->next);
        sizev.push_back(sizev[sizev.size()-1]-1);
        return root[root.size()-2]->value;
    }

    data_type current_top() {
        if (root.empty() || root[root.size()-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        return root[root.size()-1]->value;
    }

    void persistent_push_version(const int version, const data_type& value) {
        if (version >= root.size()) throw std::runtime_error("Version does not exist");
        std::shared_ptr<persistent_stack_node> next = (version == 0) ? nullptr : root[version-1];
        auto node = std::make_shared<persistent_stack_node>(value, next);
        root.push_back(node);
        if (version == 0) sizev.push_back(1);
        else sizev.push_back(sizev[version-1]+1);
    }

    data_type persistent_pop_version(const int version) {
        if (version >= root.size()) throw std::runtime_error("Version does not exist");
        if (root.empty() || root[version-1] == nullptr || version == 0) throw std::runtime_error("Stack is empty in current version");
        root.push_back(root[version-1]->next);
        sizev.push_back(sizev[version-1]-1);
        return root[version-1]->value;
    }

    data_type top_version(const int version) {
        if (version >= root.size()) throw std::runtime_error("Version does not exist");
        if (root.empty() || root[version-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        return root[version-1]->value;
    }

    size_t size() {
        if (sizev.empty()) return 0;
        return sizev[sizev.size()-1];
    }
    size_t size_version(const int version) {
        if (version >= root.size()) throw std::runtime_error("Version does not exist");
        return sizev[version-1];
    }
};





template<typename data_type>
struct persistent_queue {
    persistent_stack<data_type> stack1, stack2;
    std::vector<std::pair<int, int>> versions;
    std::vector<std::pair<int, int>> attributeversions;
    int pop_count, v1, v2, size;
    persistent_queue(): pop_count(0), v1(0), v2(0) {}

    void persistent_push(const data_type& value) {
        stack1.persistent_push(value);
        ++v1; ++size;
        versions.emplace_back(v1, v2);
        attributeversions.emplace_back(pop_count, size);
    }

    void transfer() {
        int transfer_count = stack1.size()-pop_count;
        for (int i=0; i<transfer_count; ++i) {
            stack2.persistent_push(stack1.persistent_pop());
        } v1 += transfer_count; v2 += transfer_count;
        pop_count = 0;
    }

    void transfer_version(const int global_version) {
        int version1 = versions[global_version-1].first, version2 = versions[global_version-1].second;
        int transfer_count = stack1.size_version(version1)-attributeversions[global_version-1].first;
        int s1size = stack1.size_version(version1)
        stack2.persistent_push_version(version2, stack1.persistent_pop_version(version1));
        for (int i=1; i<transfer_count; ++i) {
            stack2.persistent_push(stack1.persistent_pop());
        } v2 += transfer_count;
        while (!stack1.empty()) stack1.persistent_pop();
        v1 += s1size;
        pop_count = 0;
    }

    data_type persistent_pop() {
        if (stack2.empty()) transfer();
        ++pop_count;
        ++v2;
        versions.emplace_back(v1, v2);
        return stack2.persistent_pop();
    }

    data_type front() {
        if (stack2.empty()) transfer();
        return stack2.current_top();
    }

    void persistent_push_version(const int version, const data_type& value) {
        if (version >= versions.size()) throw std::runtime_error("Version does not exist");
        stack1.persistent_push_version(versions[version-1].first, value);
        ++v1;
        versions.emplace_back(v1, v2);
    }

    data_type persistent_pop_version(const int version) {
        if (version >= versions.size()) throw std::runtime_error("Version does not exist");
        if (stack2.size_version(versions[version-1].second) == 0 && stack1.size_version(versions[version-1].first) == 0)
            throw std::runtime_error("Queue is empty at this version");
        if (stack2.size_version(versions[version-1].second) == 0) {
            transfer_version(version);
            ++pop_count;
            ++v2;
            versions.emplace_back(v1, v2);
            return stack2.persistent_pop();
        }
        pop_count = attributeversions[version-1].first + 1;
        ++v2;
        versions.emplace_back(v1, v2);
        return stack2.persistent_pop_version(versions[version-1].second);
    }

    data_type top_version(const int version) {
        if (version >= versions.size()) throw std::runtime_error("Version does not exist");
        if (stack2.size_version(versions[version-1].second) == 0 && stack1.size_version(versions[version-1].first) == 0)
            throw std::runtime_error("Queue is empty at this version");
        if (stack2.size_version(versions[version-1].second) == 0) {
            transfer_version(version);
            return stack2.current_top();
        }
        return stack2.top_version(versions[version-1].second);
    }







};

















// <>, <<, >>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}