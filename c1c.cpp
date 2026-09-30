#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n; cin >> s;
        bool correct = true;
        if (n%2==0) {
            for (int i=0; i<n; i += 2) {
                if (s[i] == s[i+1] && s[i] != '?') correct = false;
            }
        } else {
            if (s[0] == 'b') correct = false;
            for (int i=1; i<n; i += 2) {
                if (s[i] == s[i+1] && s[i] != '?') correct = false;
            }
        }
        if (correct) cout << "YES\n";
        else cout << "NO\n";
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