#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool search(int n, vector<int>& a, int x) {
    //vector<int>::iterator it = lower_bound(a.begin(), a.end(), x);
    //return it != a.end() && *it == x;
    return binary_search(a.begin(), a.end(), x);
}





// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int k; cin>> k;
    int temp; vector<int> v;
    for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
    while (k--) {
        int q;
        cin >> q;
        cout << search(n, v, q) ? "YES\n" : "NO\n";
    }

}