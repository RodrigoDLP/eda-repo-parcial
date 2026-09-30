#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int temp, n, q;
        vector<int> v, v2;
        cin >> n; cin >> q;

        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        for (int i=0; i<n; ++i) {cin >> temp; v2.push_back(temp);}
        for (int i=0; i<n; ++i) v2[i] = max(v[i], v2[i]);
        for (int i=n-1; i>=1; --i) if (v2[i]>v2[i-1]) v2[i-1] = v2[i];
        v[0] = v2[0];
        for (int i=1; i<n; ++i) v[i] = v[i-1]+v2[i];
        for (int i=0; i<=q-1; ++i) {
            int l, r;
            cin >> l; cin >> r;
            int output = v[r-1];
            if (l > 1) output -= v[l-2];
            cout << output;
            if (i < q-1) cout << " ";
        } cout << "\n";
    }
    return 0;
}


/* SEPARATE INT INTO DIGITS
int i=0;
while (num > 0) {
    num1 = (num % (static_cast<ll>(pow(10,i+1))));
    num2 = num1 / static_cast<ll>(pow(10,i));
    num -= num1;
    //NUM2 = dígito extraído en este paso
    ++i;
}
*/