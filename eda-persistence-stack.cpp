#include <bits/stdc++.h>
using namespace std;
//Persistencia total
template<typename T>
struct PersistentStack {
    struct StackNode {
        T data;
        StackNode* next;
    };
    vector<StackNode*> version_roots;
    PersistentStack() {version_roots.push_back(nullptr);} //inicia con v0 = vacío
    void update_push(int version, T data) {
        version_roots.emplace_back(new StackNode(data, version_roots[version]));
    }
    void update_pop(int version) {
        version_roots.emplace_back(version_roots[version]->next);
        //la raíz es el top del stack, next es el siguiente top
    }
    T top(int version) {return version_roots[version]->data;}
    T top() {return version_roots[version_roots.size()-1]->data;}
};


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}