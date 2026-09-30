#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        deque<int> d;
        int n, c;
        int temp;
        ll score = 0;
        cin >> n; cin >> c;
        for (int i=0; i<n; ++i) {cin >> temp; d.push_back(temp);}
        sort(d.begin(), d.end());
        while (!d.empty() && d[0] <= c) {
            score += d[d.size()-1]-c;
            d.pop_back();
            if (!d.empty()) d.pop_front();
        }
        while (!d.empty()) {score += d[0]-c; d.pop_front();}
        cout << score << "\n";
    }
    return 0;
}