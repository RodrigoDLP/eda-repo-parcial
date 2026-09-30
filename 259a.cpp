#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string n; cin >> n; int j=0;
    for (int i=0; i<n.size(); ++i) {
        if (n[i] == '0') {j=i; break;}
    }
    cout << n.substr(0, j);
    if (j+1 < n.size()) cout << n.substr(j+1, n.size()-j-1);
    cout << "\n";
    return 0;
}