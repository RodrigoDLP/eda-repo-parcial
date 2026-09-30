#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k, temp;
        vector<int> v;
        cin >> n;
        cin >> k;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        int i=0;
        int hikes = 0;
        int daycounter=0;
        while (i<v.size()) {
            if (v[i]==0) daycounter++;
            else daycounter = 0;
            if (daycounter == k) {++hikes; ++i; daycounter = 0;}
            ++i;
        }
        cout << hikes << "\n";
    }
    return 0;
}