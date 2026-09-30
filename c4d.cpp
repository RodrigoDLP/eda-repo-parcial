#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;



//probando si hay TLE

bool equivalent(string& s1, string& s2, int left, int left2, int size) {
    bool stilltrue = true;
    for (int i=0; i<size; ++i) if (s1[i+left] != s2[i+left2]) stilltrue = false;
    if (stilltrue) return true;
    if (size % 2 == 1) return false;
    return equivalent(s1, s2, left, left2, size/2) && equivalent(s1, s2, left+size/2, left2+size/2, size/2) ||
        equivalent(s1, s2, left, left2+size/2, size/2) && equivalent(s1, s2, left+size/2, left2, size/2);
}

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2; cin >> s1 >> s2;
    bool result = equivalent(s1, s2, 0, 0, s1.size());
    if (result) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}