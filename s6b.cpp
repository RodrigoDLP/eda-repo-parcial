#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;  cin >> T;
    while (T--) {
        int n; cin >> n;
        int current = 0;
        deque<int> v(n); for (int i=0; i<n; ++i) cin >> v[i];
        priority_queue<int, vector<int, greater<int>>> pq(greater<int>());
        sort(v.begin(), v.end());
        int c = v[0];
        while (v.front() == c) {
            ++current; v.pop_front();

        }

    }
}