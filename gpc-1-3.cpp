#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    unordered_set<pair<int, int>> s;
    int temp;
    for (int i=1; i<=n; ++i) {cin >> temp; s.insert(make_pair(temp, i));}
    vector<bool>
}