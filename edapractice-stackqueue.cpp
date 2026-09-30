#include <bits/stdc++.h>
#include <cassert>
#include <stdexcept>
using namespace std;


template<typename data_type>
struct MyQueue {
    std::stack<data_type> stack1, stack2;
    size_t sz = 0;
    data_type tail = data_type();
    void push(const data_type& value) {
        stack1.push(value); ++sz;
        tail = value;
    }
    void transfer() {
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    data_type pop() {
        if (stack1.empty() && stack2.empty()) throw std::runtime_error("queue is empty");
        if (stack2.empty()) transfer();
        --sz;
        if (stack2.empty()) throw std::runtime_error("defies logic");
        data_type output = stack2.top();
        stack2.pop();
        if (stack1.empty() && stack2.empty()) tail = data_type();
        return output;
    }
    data_type front() {
        if (stack2.empty()) transfer();
        if (stack2.empty()) throw std::runtime_error("defies logic");
        return stack2.top();
    }
    data_type back() {
        //if (stack1.empty()) throw std::runtime_error("error is here");
        return tail;
    }
    size_t size() {return sz;}
    bool empty() {return sz == 0;}
};


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
        stack1.persistent_push(value); v1++; sz++; tail = value; add_version();
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


using Queue = persistent_queue<int>;

void test_initial_state() {
    Queue q;

    assert(q.current_size() == 0);

    std::cout << "[OK] initial state\n";
}

void test_normal_push() {
    Queue q;

    q.persistent_push(10);

    assert(q.current_size() == 1);
    assert(q.current_front() == 10);
    assert(q.current_back() == 10);

    q.persistent_push(20);

    assert(q.current_size() == 2);
    assert(q.current_front() == 10);
    assert(q.current_back() == 20);

    q.persistent_push(30);

    assert(q.current_size() == 3);
    assert(q.current_front() == 10);
    assert(q.current_back() == 30);

    std::cout << "[OK] normal push\n";
}

void test_fifo_order() {
    Queue q;

    q.persistent_push(10);
    q.persistent_push(20);
    q.persistent_push(30);

    assert(q.persistent_pop() == 10);
    assert(q.current_size() == 2);
    assert(q.current_front() == 20);
    assert(q.current_back() == 30);

    assert(q.persistent_pop() == 20);
    assert(q.current_size() == 1);
    assert(q.current_front() == 30);
    assert(q.current_back() == 30);

    assert(q.persistent_pop() == 30);
    assert(q.current_size() == 0);

    std::cout << "[OK] FIFO order\n";
}

void test_current_front_and_back() {
    Queue q;

    q.persistent_push(10);

    assert(q.current_front() == 10);
    assert(q.current_back() == 10);

    q.persistent_push(20);

    assert(q.current_front() == 10);
    assert(q.current_back() == 20);

    q.persistent_push(30);

    assert(q.current_front() == 10);
    assert(q.current_back() == 30);

    q.persistent_pop();

    assert(q.current_front() == 20);
    assert(q.current_back() == 30);

    std::cout << "[OK] current front/back\n";
}

void test_version_creation_with_push() {
    Queue q;

    // v0 = []
    assert(q.size_version(0) == 0);

    // v1 = [10]
    q.persistent_push(10);

    assert(q.size_version(0) == 0);

    assert(q.size_version(1) == 1);
    assert(q.front_version(1) == 10);
    assert(q.back_version(1) == 10);

    // v2 = [10, 20]
    q.persistent_push(20);

    assert(q.size_version(0) == 0);

    assert(q.size_version(1) == 1);
    assert(q.front_version(1) == 10);
    assert(q.back_version(1) == 10);

    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 10);
    assert(q.back_version(2) == 20);

    // v3 = [10, 20, 30]
    q.persistent_push(30);

    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    std::cout << "[OK] versions created by push\n";
}

void test_version_creation_with_pop() {
    Queue q;

    // v1 = [10]
    q.persistent_push(10);

    // v2 = [10, 20]
    q.persistent_push(20);

    // v3 = [10, 20, 30]
    q.persistent_push(30);

    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    // v4 = [20, 30]
    assert(q.persistent_pop() == 10);

    assert(q.current_size() == 2);
    assert(q.current_front() == 20);
    assert(q.current_back() == 30);

    // v3 debe seguir intacta
    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    // v4
    assert(q.size_version(4) == 2);
    assert(q.front_version(4) == 20);
    assert(q.back_version(4) == 30);

    std::cout << "[OK] versions created by pop\n";
}

void test_push_version() {
    Queue q;

    // v1 = [10]
    q.persistent_push(10);

    // v2 = [10, 20]
    q.persistent_push(20);

    // Partimos de v1:
    // v3 = [10, 30]
    q.persistent_push_version(1, 30);

    // v0
    assert(q.size_version(0) == 0);

    // v1
    assert(q.size_version(1) == 1);
    assert(q.front_version(1) == 10);
    assert(q.back_version(1) == 10);

    // v2
    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 10);
    assert(q.back_version(2) == 20);

    // v3
    //cout <<q.size_version(3) << "\n";
    assert(q.size_version(3) == 2);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    // v2 no debe haberse modificado
    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 10);
    assert(q.back_version(2) == 20);

    std::cout << "[OK] push from previous version\n";
}

void test_pop_version() {
    Queue q;

    // v1 = [10]
    q.persistent_push(10);

    // v2 = [10, 20]
    q.persistent_push(20);

    // v3 = [10, 20, 30]
    q.persistent_push(30);

    // Pop desde v2:
    // v4 = [20]
    assert(q.persistent_pop_version(2) == 10);

    assert(q.size_version(4) == 1);
    assert(q.front_version(4) == 20);
    assert(q.back_version(4) == 20);

    // v2 debe seguir intacta
    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 10);
    assert(q.back_version(2) == 20);

    // v3 también
    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    std::cout << "[OK] pop from previous version\n";
}

void test_front_version() {
    Queue q;

    q.persistent_push(10); // v1
    q.persistent_push(20); // v2
    q.persistent_push(30); // v3

    assert(q.front_version(1) == 10);
    assert(q.front_version(2) == 10);
    assert(q.front_version(3) == 10);

    q.persistent_pop(); // v4 = [20,30]

    assert(q.front_version(3) == 10);
    assert(q.front_version(4) == 20);

    std::cout << "[OK] front_version\n";
}

void test_back_version() {
    Queue q;

    q.persistent_push(10); // v1
    q.persistent_push(20); // v2
    q.persistent_push(30); // v3

    assert(q.back_version(1) == 10);
    assert(q.back_version(2) == 20);
    assert(q.back_version(3) == 30);

    q.persistent_pop(); // v4 = [20,30]

    assert(q.back_version(3) == 30);
    assert(q.back_version(4) == 30);

    std::cout << "[OK] back_version\n";
}

void test_size_version() {
    Queue q;

    assert(q.size_version(0) == 0);

    q.persistent_push(10); // v1
    q.persistent_push(20); // v2
    q.persistent_push(30); // v3

    assert(q.size_version(0) == 0);
    assert(q.size_version(1) == 1);
    assert(q.size_version(2) == 2);
    assert(q.size_version(3) == 3);

    q.persistent_pop(); // v4

    assert(q.size_version(3) == 3);
    assert(q.size_version(4) == 2);

    std::cout << "[OK] size_version\n";
}

void test_branching_versions() {
    Queue q;

    // v1 = [10]
    q.persistent_push(10);

    // v2 = [10, 20]
    q.persistent_push(20);

    // v3 = [10, 20, 30]
    q.persistent_push(30);

    // Desde v1:
    // v4 = [10, 40]
    q.persistent_push_version(1, 40);

    assert(q.size_version(1) == 1);
    assert(q.front_version(1) == 10);
    assert(q.back_version(1) == 10);

    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 10);
    assert(q.back_version(2) == 20);

    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    assert(q.size_version(4) == 2);
    assert(q.front_version(4) == 10);
    assert(q.back_version(4) == 40);

    // Desde v2:
    // v5 = [10, 20, 50]
    q.persistent_push_version(2, 50);

    assert(q.size_version(5) == 3);
    assert(q.front_version(5) == 10);
    assert(q.back_version(5) == 50);

    // Las ramas anteriores siguen intactas
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    assert(q.front_version(4) == 10);
    assert(q.back_version(4) == 40);

    std::cout << "[OK] branching versions\n";
}

void test_branching_with_pop() {
    Queue q;

    // v1 = [1]
    q.persistent_push(1);

    // v2 = [1,2]
    q.persistent_push(2);

    // v3 = [1,2,3]
    q.persistent_push(3);

    // Desde v3:
    // v4 = [2,3]
    q.persistent_pop_version(3);

    assert(q.size_version(4) == 2);
    assert(q.front_version(4) == 2);
    assert(q.back_version(4) == 3);

    // Desde v2:
    // v5 = [2]
    q.persistent_pop_version(2);

    assert(q.size_version(5) == 1);
    assert(q.front_version(5) == 2);
    assert(q.back_version(5) == 2);

    // Todas las versiones originales siguen intactas
    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 1);
    assert(q.back_version(2) == 2);

    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 1);
    assert(q.back_version(3) == 3);

    std::cout << "[OK] branching with pop\n";
}

void test_current_version_after_version_operation() {
    Queue q;

    // v1 = [10]
    q.persistent_push(10);

    // v2 = [10, 20]
    q.persistent_push(20);

    // Partimos de v1:
    // v3 = [10, 30]
    q.persistent_push_version(1, 30);

    // La versión actual debe ser v3
    assert(q.current_size() == 2);
    assert(q.current_front() == 10);
    assert(q.current_back() == 30);

    // Pop normal desde v3:
    // v4 = [30]
    assert(q.persistent_pop() == 10);

    assert(q.current_size() == 1);
    assert(q.current_front() == 30);
    assert(q.current_back() == 30);

    // v3 sigue intacta
    assert(q.size_version(3) == 2);
    assert(q.front_version(3) == 10);
    assert(q.back_version(3) == 30);

    // v4
    assert(q.size_version(4) == 1);
    assert(q.front_version(4) == 30);
    assert(q.back_version(4) == 30);

    std::cout << "[OK] current version after version operation\n";
}


void test_complex_persistence() {
    Queue q;

    // v1 = [1]
    q.persistent_push(1);

    // v2 = [1, 2]
    q.persistent_push(2);

    // v3 = [1, 2, 3]
    q.persistent_push(3);

    // v4 = [2, 3]
    q.persistent_pop();

    // v5 = [2, 3, 4]
    q.persistent_push(4);

    // Desde v2:
    // v6 = [2]
    assert(q.persistent_pop_version(2) == 1);

    // Desde v2:
    // v7 = [1, 2, 5]
    q.persistent_push_version(2, 5);

    // v0 = []
    assert(q.size_version(0) == 0);

    // v1 = [1]
    assert(q.size_version(1) == 1);
    assert(q.front_version(1) == 1);
    assert(q.back_version(1) == 1);

    // v2 = [1, 2]
    assert(q.size_version(2) == 2);
    assert(q.front_version(2) == 1);
    assert(q.back_version(2) == 2);

    // v3 = [1, 2, 3]
    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 1);
    assert(q.back_version(3) == 3);

    // v4 = [2, 3]
    std::cout << "v4 queue:\n";
    std::cout << "size = " << q.size_version(4) << "\n";
    std::cout << "front = " << q.front_version(4) << "\n";
    std::cout << "back = " << q.back_version(4) << "\n";

    std::cout << "queue tuple v4:\n";
    std::cout << "v1 = " << std::get<0>(q.versions[3]) << "\n";
    std::cout << "v2 = " << std::get<1>(q.versions[3]) << "\n";
    std::cout << "size = " << std::get<2>(q.versions[3]) << "\n";
    std::cout << "tail = " << std::get<3>(q.versions[3]) << "\n";
    assert(q.size_version(4) == 2);
    assert(q.front_version(4) == 2);
    assert(q.back_version(4) == 3);

    // v5 = [2, 3, 4]
    assert(q.size_version(5) == 3);
    assert(q.front_version(5) == 2);
    assert(q.back_version(5) == 4);

    // v6 = [2]
    assert(q.size_version(6) == 1);
    assert(q.front_version(6) == 2);
    assert(q.back_version(6) == 2);

    // v7 = [1, 2, 5]
    assert(q.size_version(7) == 3);
    assert(q.front_version(7) == 1);
    assert(q.back_version(7) == 5);

    std::cout << "[OK] complex persistence\n";
}


void test_repeated_push_pop() {
    Queue q;

    // Añadimos 100 elementos
    for (int i = 1; i <= 100; ++i) {
        q.persistent_push(i);
    }

    assert(q.current_size() == 100);
    assert(q.current_front() == 1);
    assert(q.current_back() == 100);

    // Sacamos los primeros 50
    for (int i = 1; i <= 50; ++i) {
        assert(q.persistent_pop() == i);
    }

    assert(q.current_size() == 50);
    assert(q.current_front() == 51);
    assert(q.current_back() == 100);

    // Añadimos otros 50
    for (int i = 101; i <= 150; ++i) {
        q.persistent_push(i);
    }

    assert(q.current_size() == 100);
    assert(q.current_front() == 51);
    assert(q.current_back() == 150);

    // Comprobar FIFO del resto
    for (int i = 51; i <= 150; ++i) {
        assert(q.persistent_pop() == i);
    }

    assert(q.current_size() == 0);

    std::cout << "[OK] repeated push/pop\n";
}


void test_old_versions_after_many_operations() {
    Queue q;

    // v1 = [1]
    q.persistent_push(1);

    // v2 = [1, 2]
    q.persistent_push(2);

    // v3 = [1, 2, 3]
    q.persistent_push(3);

    // v4 = [2, 3]
    q.persistent_pop();

    // v5 = [2, 3, 4]
    q.persistent_push(4);

    // v6 = [2, 3, 4, 5]
    q.persistent_push(5);

    // v7 = [3, 4, 5]
    q.persistent_pop();

    // v8 = [1, 100]
    q.persistent_push_version(1, 100);

    // v9 = [2]
    assert(q.persistent_pop_version(2) == 1);

    // v3 debe continuar siendo exactamente [1, 2, 3]
    assert(q.size_version(3) == 3);
    assert(q.front_version(3) == 1);
    assert(q.back_version(3) == 3);

    // v6 debe continuar siendo [2, 3, 4, 5]
    assert(q.size_version(6) == 4);
    assert(q.front_version(6) == 2);
    assert(q.back_version(6) == 5);

    // v8 = [1, 100]
    assert(q.size_version(8) == 2);
    assert(q.front_version(8) == 1);
    assert(q.back_version(8) == 100);

    // v9 = [2]
    assert(q.size_version(9) == 1);
    assert(q.front_version(9) == 2);
    assert(q.back_version(9) == 2);

    std::cout << "[OK] old versions remain unchanged\n";
}


int main() {
    /*test_initial_state();

    test_normal_push();
    test_fifo_order();
    test_current_front_and_back();

    test_version_creation_with_push();
    test_version_creation_with_pop();

    test_push_version();
    test_pop_version();

    test_front_version();
    test_back_version();
    test_size_version();

    test_branching_versions();
    test_branching_with_pop();

    test_current_version_after_version_operation();


    test_complex_persistence();
    test_repeated_push_pop();
    test_old_versions_after_many_operations();*/

    std::cout << "\nAll tests passed!\n";

    return 0;
}