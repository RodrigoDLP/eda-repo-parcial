#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    string s;
    for (int test=1; test<=T; ++test) {
        cin >> s;
        int counter = 0;
        for (int i=0; i<s.size(); ++i) {
            if (!(s[i] != '-' ||
                i+1<s.size() && (s[i+1] == 'S' || s[i+1] == 'B')  ||
                i+2 < s.size() && s[i+2] == 'B' ||
                i > 1 && s[i-1] == 'S')) ++counter;
        }
        cout << "Case #" << test << ": " << counter << "\n";
    }
    return 0;
}