#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> add_to_half(unordered_set<int>& added, vector<int> v1, int b) {
    int a = v1.size();
    for (int i=0; i<a; ++i) if (!added.count(v1[i]+a)) {v1.push_back(v1[i]+a); added.insert(v1[i]+a);}
    return v1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n); for (int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(), v.end());
    vector<int> curr = {0};
    unordered_set<int> added;
    for (int i=0; i<n; ++i) {
        curr = add_to_half(added, curr, v[i]);
    }

}