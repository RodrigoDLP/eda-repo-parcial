#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string temp;
        cin >> temp;
        deque<int> d, d2;
        for (int i=0; i<temp.size(); ++i) {
            if (temp[i] == 'l') d.push_front(i+1);
            else d2.push_back(i+1);
        }
        for (const auto& e: d2) cout << e << "\n";
        for (const auto& e: d) cout << e << "\n";

    return 0;
}