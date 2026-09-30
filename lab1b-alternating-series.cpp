#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 2) {
            cout << -1 << "\n";
            cout << 2 << "\n";
        } else {

            if (n % 2 == 1) {
                for (int i=0; i<n-1; i += 2) {
                    cout << -1 << "\n";
                    cout << 3 << "\n";
                }
                cout << -1 << "\n";
            } else {
                for (int i=0; i<n-3; i += 2) {
                    cout << -1 << "\n";
                    cout << 3 << "\n";
                }
                cout << -1 << "\n";
                cout << 2 << "\n";
            }
        }
    }
    return 0;
}
