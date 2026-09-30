#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        vector<int> v;
        int temp, n;
        int counter = 0;
        cin >> n;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        for (int i=0; i<n; ++i) {
            cin >> temp;
            if (v[i] - temp > 0) counter += (v[i]-temp);
        }
        ++counter;
        cout << counter << "\n";
    }
    return 0;
}