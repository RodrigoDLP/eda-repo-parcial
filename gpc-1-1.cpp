#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct trie {
    struct trienode {
        vector<trienode*> children;
        bool isleaf;
        trienode(): isleaf(false) {children.assign(26, nullptr);}
        ~trienode() {for (auto e: children) if (e) {delete e; e = nullptr;} children.clear();}
    };
    trienode* root;
    void insert(const string& word) {
        trienode* curr = root;
        for (const char c: word) {
            if (!curr->children[c-'a']) curr->children[c-'a'] = new trienode();
            curr = curr->children[c-'a'];
        }
        curr->isleaf = true;
    }
    bool search(const string& word, bool prefix) {
        trienode* curr = root;
        for (const char c: word) {
            if (!curr->children[c-'a']) return false;
            curr = curr->children[c-'a'];
        } return prefix || curr->isleaf;
    }

    bool remove(const string& word) {
        stack<trienode*> s;
        trienode* curr = root;
        for (const char c: word) {
            s.push(curr);
            if (!curr->children[c-'a']) return false;
            curr = curr->children[c-'a'];
        }
        if (!curr->isleaf) return false;
        curr->isleaf = false;
        for (auto e: s.top()->children) {
            if (e != nullptr) return true;
        }
        int currindex = word.size()-1;
        while (!s.empty()) {
            if (s.top()->isleaf) return true;
            delete s.top();
            s.pop();
            if (s.empty()) root = nullptr;
            else {
                s.top()->children[currindex] = nullptr;
                --currindex;
            }
        }
    }
    ~trie() {if (root) delete root; root = nullptr;}
};







int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

}