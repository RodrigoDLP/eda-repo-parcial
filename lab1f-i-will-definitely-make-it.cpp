#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k, temp;
        bool correct = true;
        cin >> n; cin >> k;
        vector<int> v;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        int start = v[k-1];
        sort(v.begin(), v.end());
        for (int i=0; i<n-1; ++i) {if (v[i+1]-v[i] > start) correct = false;}
        if (correct) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}