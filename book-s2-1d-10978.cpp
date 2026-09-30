#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string temp; cin >> temp; string temp2;
    vector<string> v(n);
    int counter = -1;
    bool valid = true;
    while (temp != "0") {
        cin >> temp2;
        counter += temp2.size();
        if (v[counter % n] != "") {cout << "-1\n"; valid = false; break;}
        v[counter % n] = temp;
        cin >> temp;
    }
    if (valid) {
        for (auto e: v) cout << v << " ";
        cout << "\n";
    }
    return 0;
}
