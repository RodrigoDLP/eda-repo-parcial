#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        ll temp, n;
        vector<ll> v;
        cin >> n;
        ll maxglobal = 0;
        ll sumaglobal = 0;
        ll noceros = 0;
        for (int i=0; i<n; ++i) {
            cin >> temp; v.push_back(temp); if (temp > maxglobal) maxglobal = temp;
            sumaglobal += temp;
            if (temp != 0) noceros++;
        }
        if (sumaglobal == n) cout << 1 << "\n";
        else if (sumaglobal - noceros >= n) cout << noceros << "\n"; //sumaglobal no puede ser < n
        else {
            cout << sumaglobal-n+1   << "\n"; //es posible que sea solo esto pero ya me da flojera cambiarlo
        }
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