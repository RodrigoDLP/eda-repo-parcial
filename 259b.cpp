#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int temp; vector<int> v; v.reserve(9);
    for (int i=0; i<9; ++i) {cin >> temp; v.push_back(temp);}
    int a = v[1] + v[2];
    int b = v[3] + v[5];
    int c = v[6] + v[7];
    int d = min({a, b, c});
    a = d-a; b = d-b; c = d-c;
    int e = (v[1] + v[2] - b - c)/2;
    v[0] = a + e;
    v[4] = b + e;
    v[8] = c + e;
    for (int i=0; i<3; ++i) cout << v[i] << " "; cout << "\n";
    for (int i=3; i<6; ++i) cout << v[i] << " "; cout << "\n";
    for (int i=6; i<9; ++i) cout << v[i] << " "; cout << "\n";
    return 0;
}