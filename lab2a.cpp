#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    string s;
    while (T--) {
        stack<char> stack;
        cin >> s;
        bool valid = true;
        for (auto c: s) {
            if (c == '(' || c == '[' || c == '{') stack.push(c);
            else if (c == ')') {
                if (stack.empty() || stack.top() != '(') {valid = false; break;}
                else stack.pop();
            } else if (c == ']') {
                if (stack.empty() || stack.top() != '[') {valid = false; break;}
                else stack.pop();
            } else if (c == '}') {
                if (stack.empty() || stack.top() != '{') {valid = false; break;}
                else stack.pop();
            }
        }
        if (valid == true && stack.empty()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}