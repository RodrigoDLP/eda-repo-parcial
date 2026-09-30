#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        string a, b; cin >> a; cin >> b;
        int evensum1 = 0;
        int oddsum1 = 0;
        int evencount1 = 0;
        int oddcount1 = 0;
        int evensum2 = 0;
        int oddsum2 = 0;
        int evencount2 = 0;
        int oddcount2 = 0;
        for (int i=0; i<n; ++i) {
            if (a[i] == '1') {
                if (i % 2 == 0) {evensum1 += i; evencount1++;}
                else {oddsum1 += i; oddcount1++;}
            }
            if (b[i] == '1') {
                if (i % 2 == 0) {evensum2 += i; evencount2++;}
                else {oddsum2 += i; oddcount2++;}
            }
        }
        if (evencount1 != evencount2 || oddcount1 != oddcount2) cout << -1 << "\n";
        else {
            cout << (abs(evensum1-evensum2)+abs(oddsum1-oddsum2))/2 << "\n";
        }
    }
    return 0;
}


/* SEPARATE INT INTO DIGITS
int i=0;
int num;
int num1, num2;
while (num > 0) {
    num1 = (num % (static_cast<ll>(pow(10,i+1))));
    num2 = num1 / static_cast<ll>(pow(10,i));
    num -= num1;
    //NUM2 = dígito extraído en este paso
    ++i;
}
*/