#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    int temp;

    for (int test=1; test<=T; ++test) {
        set<int> t, t2, t3;
        int n;
        cin >> n;
        for (int j=0; j<n; ++j) {
            cin >> temp;
            t.insert(temp);
        }
        cin >> n;
        for (int j=0; j<n; ++j) {
            cin >> temp;
            if (!t.count(temp)) t2.insert(temp);
            if (t.count(temp)) t.erase(temp);
        }
        cin >> n;
        for (int j=0; j<n; ++j) {
            cin >> temp;
            if (!t.count(temp) && !t2.count(temp)) t3.insert(temp);
            if (t.count(temp)) t.erase(temp);
            if (t2.count(temp)) t2.erase(temp);
        }
        cout << "Case #" << test << ":\n";
        if (max({t.size(), t2.size(), t3.size()}) == t.size()) {
            cout << "1 "; cout << t.size() << " "; for (auto e: t) cout << e << " "; cout << "\n";
        }
        if (max({t.size(), t2.size(), t3.size()}) == t2.size()) {
            cout << "2 "; cout << t2.size() << " "; for (auto e: t2) cout << e << " "; cout << "\n";
        }
        if (max({t.size(), t2.size(), t3.size()}) == t3.size()) {
            cout << "3 "; cout << t3.size() << " "; for (auto e: t3) cout << e << " "; cout << "\n";
        }

    }
    return 0;
}


