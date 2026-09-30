#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n; int temp;
        vector<int> v;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        sort(v.begin(), v.end(), greater<int>());
        if (v[0] == v[v.size()-1]) cout << "NO\n";
        else {
            cout << "YES\n";
           swap(v[1], v[v.size()-1]);
           for (int i=0; i<v.size(); ++i) cout << v[i] << " ";
            cout << "\n";
        }
    }
}