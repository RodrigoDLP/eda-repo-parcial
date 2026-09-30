#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; ll temp; ll global_sum = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i=0; i<n; ++i) {
        cin >> temp;
        if (temp == 1) {
            cin >> temp;
            pq.push(temp-global_sum);
        } else if (temp == 2) {
            cin >> temp;
            global_sum += temp;
        } else {
            ll t = pq.top();
            ll result = t + global_sum;
            cout << result << "\n";
            pq.pop();
        }
    }
}