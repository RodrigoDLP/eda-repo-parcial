#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n; cin >> k; int temp;
    vector<int> v; for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
    int i=0;
    ll counter = 0;
    int minabs = INT_MAX;
    while (i != min(n, k)) {
        if (abs(v[i]) < minabs) minabs = abs(v[i]);
        counter += abs(v[i]);
        ++i;
    }
    while (i != n) {counter += v[i]; ++i;}
    if ((k > n && (k-n)%2==1) || v[0] > 0 && k % 2 == 1) counter -= 2*minabs;
    cout << counter << "\n";
        return 0;
}