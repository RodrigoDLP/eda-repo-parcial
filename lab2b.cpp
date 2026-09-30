#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int temp1, temp2;
        int n;
        ll k;
        cin >> n; cin >> k; cin >> temp1; cin >> temp2;
        int maxactual = max(temp1, temp2);
        int streak=1;
        if (k == 1) cout << maxactual << "\n";
        else if (k >= n) {
            for (int i=2; i<n; ++i) {
                cin >> temp1;
                if (temp1 > maxactual) maxactual = temp1;
            }
            cout << maxactual << "\n";
        }
        else {
            for (int i=2; i<n; ++i) {
                cin >> temp1;
                if (temp1 > maxactual) {streak = 1; maxactual = temp1;}
                else ++streak;
                if (streak >= k) break;
            }
            cout << maxactual << "\n";
    }
}