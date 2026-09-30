#include <bits/stdc++.h>
using namespace std;
//Persistencia total
template<typename T>
struct PersistentStack {
    struct StackNode {
        T data;
        StackNode* next;
        StackNode(T data, StackNode* next): data(data), next(next) {}
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
    T top(int version) {
        if (version_roots[version] == nullptr) return T(0);
        return version_roots[version]->data;
    }
    T top() {return version_roots[version_roots.size()-1]->data;}
};


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    PersistentStack<int> stack;
    int t, m;
    long long sum = 0;
    for (int i=0; i<n; ++i) {
        cin >> t; cin >> m;
        if (m == 0) stack.update_pop(t);
        else stack.update_push(t, stack.top(t)+m);
    }
    for (int i=1; i<=n; ++i) sum += stack.top(i);
    cout << sum << "\n";


}