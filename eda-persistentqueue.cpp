#include <bits/stdc++.h>
#include <cassert>
#include <stdexcept>
using namespace std;

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

    void print(const int version) {
        if (version == 0) {cout << "\n"; return;}
        auto node = root[version-1];
        while (node != nullptr) {cout << node->value << " "; node = node->next;}
    }

    void printall() {
        for (int i=0; i<root.size(); ++i) {print(i);}
    }



    void persistent_push(const data_type& value) {
        std::shared_ptr<persistent_stack_node> next = root.empty() ? nullptr : root[root.size()-1];
        auto node = std::make_shared<persistent_stack_node>(value, next);
        root.push_back(node);
        if (sizev.empty()) sizev.push_back(1);
        else sizev.push_back(sizev[sizev.size()-1]+1);
    }

    void persistent_stall() {
        if (root.empty()) root.push_back(nullptr);
        else root.push_back(root[root.size()-1]);
        if (sizev.empty()) sizev.push_back(0);
        else sizev.push_back(sizev[sizev.size()-1]);
    }

    data_type persistent_pop() {
        if (root.empty() || root[root.size()-1] == nullptr || sizev[sizev.size()-1] == 0) throw std::runtime_error("Stack is empty in current version");
        if (sizev.empty()) throw std::runtime_error("somehow, we got here");
        root.push_back(root[root.size()-1]->next);
        sizev.push_back(sizev[sizev.size()-1]-1);
        if (root.size() < 2) throw std::runtime_error("aosidfjsdoifj");
        return root[root.size()-2]->value;
    }

    data_type current_top() {
        if (root.empty() || root[root.size()-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        return root[root.size()-1]->value;
    }

    void persistent_push_version(const int version, const data_type& value) {
        if (version > root.size()) throw std::runtime_error("Version does not exist");
        std::shared_ptr<persistent_stack_node> next = version == 0 ? nullptr : root[version-1];
        auto node = std::make_shared<persistent_stack_node>(value, next);
        root.push_back(node);
        if (version > sizev.size()) throw std::runtime_error("pers push version size - defies logic");
        if (version == 0) sizev.push_back(1);
        else sizev.push_back(sizev[version-1]+1);
        //cout << "STACK PERS PUSH COMPLETED\n";
    }

    data_type persistent_pop_version(const int version) {
        if (version > root.size()) throw std::runtime_error("Version does not exist");
        if (version == 0 || root.empty() || root[version-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        root.push_back(root[version-1]->next);
        if (version > sizev.size()) throw std::runtime_error("pers pop version size - defies logic");
        sizev.push_back(sizev[version-1]-1);
        return root[version-1]->value;
        cout << "STACK PERS POP COMPLETED\n";
    }

    void persistent_stall_version(const int version) {
        if (root.empty() || sizev.empty()) {
            //cout << "version called: " << version << "\n";
            //throw std::runtime_error(":(2");
        }
        if (version > root.size()) throw std::runtime_error("Version does not exist");
        //cout << "we are getting here\n";
        if (version == 0) root.push_back(nullptr);
        else root.push_back(root[version-1]);
        //cout << "we are getting here maybe\n";
        if (version > sizev.size()) throw std::runtime_error("pers stall version size - defies logic");
        if (version == 0) sizev.push_back(0);
        else sizev.push_back(sizev[version-1]);
        //cout << "STACK PERS STALL COMPLETED\n";
    }

    data_type top_version(const int version) {
        if (version > root.size()) throw std::runtime_error("Version does not exist");
        if (version == 0 || root.empty() || root[version-1] == nullptr) throw std::runtime_error("Stack is empty in current version");
        return root[version-1]->value;
    }

    size_t size() {
        if (sizev.empty()) return 0;
        return sizev[sizev.size()-1];
    }
    size_t size_version(const int version) {
        if (version == 0) return 0;
        if (version > root.size()) throw std::runtime_error("Version does not exist");
        if (version > sizev.size()) throw std::runtime_error("sizeversion version size - defies logic");
        return sizev[version-1];
    }

    bool empty() {
        if (sizev.empty()) return true;
        return sizev[sizev.size()-1] == 0;
    }
};

template<typename data_type>
struct persistent_queue {
    persistent_stack<data_type> stack1, stack2;
    data_type tail = data_type(); size_t sz = 0; size_t v1 = 0, v2 = 0;
    vector<tuple<size_t, size_t, size_t, data_type>> versions;
    void add_version() {
        versions.emplace_back(v1, v2, sz, tail);
    }
    void printall() {
        for (int i=0; i<versions.size(); ++i) {
            cout << "version " << i << "\n" << "stack 1: ";
            stack1.print(get<0>(versions[i]));
            cout << "\n" << "stack 2: ";
            stack2.print(get<1>(versions[i]));
            cout << "\n";
        }
    }
    void persistent_push(const data_type& value) {
        stack1.persistent_push(value);
        stack2.persistent_stall();
        v1++; v2++; sz++; tail = value; add_version();
        //cout << "--------------------------PUSH-------------------------------\n";
        //printall();
    }
    void transfer() {
        const size_t s1size = stack1.size();
        while (!stack1.empty()) {stack2.persistent_push(stack1.persistent_pop());}
        v1 += s1size; v2 += s1size;
    }
    void transfer_version(const int version) {


        if (version > versions.size()) throw std::runtime_error("Version does not exist BUT WHY ARE WE GETTING HERE");
        //cout << "-----before transfer:--------\n";
        //printall();

        const int version1 = std::get<0>(versions[version-1]);
        const int version2 = std::get<1>(versions[version-1]);
        const size_t s1size = stack1.size_version(version1);
        /*std::cout << "\nTRANSFER VERSION " << version << "\n";
        std::cout << "source stack1 version = " << version1 << "\n";
        std::cout << "source stack2 version = " << version2 << "\n";
        std::cout << "s1size = " << s1size << "\n";

        std::cout << "stack1 current size before = "
                  << stack1.size() << "\n";

        std::cout << "stack2 current size before = "
                  << stack2.size() << "\n";
        */


        auto pop_result = stack1.persistent_pop_version(version1);
        stack2.persistent_push_version(version2, pop_result);
        while (!stack1.empty()) {stack2.persistent_push(stack1.persistent_pop());}
        v1 += s1size; v2 += s1size;
        //cout << "--------after transfer----------\n";
        //printall();
        /*std::cout << "stack1 current size after = "
          << stack1.size() << "\n";

        std::cout << "stack2 current size after = "
                  << stack2.size() << "\n";

        std::cout << "v1 = " << v1 << "\n";
        std::cout << "v2 = " << v2 << "\n";*/
    }

    data_type persistent_pop() {
        if (stack1.empty() && stack2.empty()) throw std::runtime_error("Queue is empty");
        if (stack2.empty()) transfer();
        sz--; v2++;
        data_type output = stack2.current_top(); stack2.persistent_pop();
        if (stack1.empty() && stack2.empty()) tail = data_type();
        add_version();
        //cout << "--------------------------POP-------------------------------\n";
        //printall();
        return output;
    }
    data_type current_front() {
        if (stack1.empty() && stack2.empty()) throw std::runtime_error("Queue is empty");
        if (stack2.empty()) transfer();
        //cout << "--------------------------FRONT-------------------------------\n";
        //printall();
        return stack2.current_top();
    }
    data_type current_back() {
        if (stack1.empty() && stack2.empty()) throw std::runtime_error("Queue is empty");
        //cout << "--------------------------BACK-------------------------------\n";
        //printall();
        return tail;
    }
    void persistent_push_version(const int version, const data_type& value) {
        if (version > versions.size()) throw std::runtime_error("Version does not exist");
        if (version == 0) {
            stack1.persistent_push_version(0, value);
            stack2.persistent_stall_version(0);
            //cout << "this prints\n";
            v1++; v2++;
            sz = (version == 0) ? 1 : std::get<2>(versions[version-1])+1;
            tail = value;

            add_version();
            //cout << "Hi\n";
            return;
        }
        //cout << "calling ppushv on version " << version << " for value " << value << "\n";
        stack1.persistent_push_version(std::get<0>(versions[version-1]), value);
        //cout << "calling pstallv on version " << version << " for value " << value << "\n";
        stack2.persistent_stall_version(std::get<1>(versions[version-1]));
        v1++; v2++;
        sz = (version == 0) ? 1 : std::get<2>(versions[version-1])+1;
        tail = value;
        add_version();
        //cout << "--------------------------PUSH-------------------------------\n";
        //printall();
    }
    data_type persistent_pop_version(const int version) {
        if (version > versions.size()) throw std::runtime_error("Version does not exist");
        if (version == 0) throw std::runtime_error("Queue is empty at this version");
        const int version1 = std::get<0>(versions[version-1]);
        const int version2 = std::get<1>(versions[version-1]);
        if (stack1.size_version(version1) == 0 && stack2.size_version(version2) == 0)
            throw std::runtime_error("Queue is empty at this version");
        if (stack2.size_version(version2) == 0) {
            transfer_version(version);
            sz = std::get<2>(versions[version-1])-1;
            v2++; v1++;
            data_type output = stack2.current_top(); stack2.persistent_pop();
            stack1.persistent_stall();
            tail = (stack1.empty() && stack2.empty()) ? data_type() : std::get<3>(versions[version-1]);
            add_version();
            //cout << "--------------------------POP-------------------------------\n";
            //printall();
            return output;
        }
        sz = std::get<2>(versions[version-1])-1;
        v2++;
        data_type output = stack2.top_version(version2); stack2.persistent_pop_version(version2);
        stack1.persistent_stall_version(version1);
        tail = (stack1.empty() && stack2.empty()) ? data_type() : std::get<3>(versions[version-1]);
        add_version();
        //cout << "--------------------------POP-------------------------------\n";
        //printall();
        return output;
    }
    data_type front_version(const int version) {
        if (version > versions.size()) throw std::runtime_error("Version does not exist");
        if (version == 0) throw std::runtime_error("Queue is empty at this version");
        const int version1 = std::get<0>(versions[version-1]);
        const int version2 = std::get<1>(versions[version-1]);
        if (stack1.size_version(version1) == 0 && stack2.size_version(version2) == 0)
            throw std::runtime_error("Queue is empty at this version");
        if (stack2.size_version(version2) == 0) {
            transfer_version(version);
            return stack2.current_top();
        }
        return stack2.top_version(version2);
    }
    data_type back_version(const int version) {
        if (version > versions.size()) throw std::runtime_error("Version does not exist");
        if (version == 0) throw std::runtime_error("Queue is empty at this version");
        const int version1 = std::get<0>(versions[version-1]);
        const int version2 = std::get<1>(versions[version-1]);
        if (stack1.size_version(version1) == 0 && stack2.size_version(version2) == 0)
            throw std::runtime_error("Queue is empty at this version");
        return std::get<3>(versions[version-1]);
    }
    size_t current_size() {return sz;}

    size_t size_version(const int version) {
        if (version > versions.size()) throw std::runtime_error("Version does not exist");
        if (version == 0) return 0;
        return std::get<2>(versions[version-1]);
    }

};



int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    persistent_queue<int> q;
    int n; cin >> n; int temp1, temp2, temp3;
    while (n--) {
        cin >> temp1;
        if (temp1 == 1) {
            cin >> temp2 >> temp3;
            q.persistent_push_version(temp2, temp3);
        } else if (temp1 == -1) {
            cin >> temp2;
            cout << q.front_version(temp2) << "\n";
            q.persistent_pop_version(temp2);
        } else throw std::runtime_error(":(((((((((");
    }
}