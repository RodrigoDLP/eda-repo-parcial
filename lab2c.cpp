#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int temp1, temp2;
    int n;
    int k;
    cin >> n; cin >> k;
    vector<int> v;
    for (int i=0; i<n; ++i) {
        cin >> temp1; cin >> temp2;
        v.push_back(temp2);
        v.push_back(temp1-temp2);
    }
    sort(v.begin(), v.end(), greater<int>()); //accumulate
    ll counter = 0;
    for (int i=0; i<min(2*n, k); ++i) counter += v[i];
    cout << counter << "\n";
}