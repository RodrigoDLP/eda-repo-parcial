#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k, temp;
        cin >> n;
        cin >> k;
        vector<int> v, v2, v3;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(min(temp % k, abs((temp%k)-k)));}
        for (int i=0; i<n; ++i) {cin >> temp; v2.push_back(min(temp % k, abs((temp%k)-k)));}
        sort(v.begin(), v.end());
        sort(v2.begin(), v2.end());
        bool correct = true;
        for (int i=0; i<n; ++i) {
            if (v[i]!=v2[i]) {
                correct = false;
                break;
            }
        }
        if (correct) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}