#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k, m; cin >> n >> k >> m;
        unordered_set<char> setcito;
        string s; cin >> s;
        int laps = 0;
        string counterexample = "";
        for (const char c: s) {
            setcito.insert(c);
            if (setcito.size() == k) {
                counterexample += c;
                ++laps;
                setcito.clear();
            }
        }
        if (laps >= n) {
            cout << "YES\n";
        } else {
            string chars = "abcdefghijklmnopqrstuvwxyz";
            for (const char c: chars) {if (!setcito.count(c)) {counterexample += c; break; }}
            while (counterexample.size() < n) counterexample += 'a';
            cout << "NO\n";
            cout << counterexample << "\n";
        }
    }
}