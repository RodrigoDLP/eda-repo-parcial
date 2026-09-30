#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int a[n]; int b[n];
        int temp;
        for (int i=0; i<n; ++i) {cin >> temp; a[i] = temp;}
        for (int i=0; i<n; ++i) {cin >> temp; b[i] = temp;}
        int counter = 0;
        int zerocounter = 0;
        for (int i=0; i<n; ++i) {
            if (a[i] != b[i]) {
                if (a[i] == 1) ++counter; else ++zerocounter;
            }
        }
        if (counter == 0 && zerocounter == 0) cout << 0 << "\n";
        else if (counter == 0) cout << -1 << "\n";
        else if (counter % 2 == 0) cout << 2 << "\n";
        else cout << 1 << "\n";
    }
    return 0;
}
