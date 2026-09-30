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
        string s; cin >> s;
        vector<int> zeros, ones;
        int currzeros = 0;
        int currones = 0;
        int leftedgezeros = 0;
        int rightedgezeros = 0;
        int leftedgeones = 0;
        int rightedgeones = 0;
        for (int i=0; i<n; ++i) {
            if (s[i] == '0') {
                ++currzeros;
                if (currones != 0) ones.push_back(currones);
                currones = 0;
            } else {
                ++currones;
                if (currzeros != 0) zeros.push_back(currzeros);
                currzeros = 0;
            }
        }
        if (s[0] == '0') leftedgezeros = zeros[0];
        else leftedgeones = ones[0];
        if (s[n-1] == '0') rightedgezeros = zeros[zeros.size()-1];
        else rightedgeones = ones[ones.size()-1];
        sort(zeros.begin(), zeros.end(), greater<>());
        sort(ones.begin(), ones.end(), greater<>());
        int i=0; int j=0;


    }
    return 0;
}


/* SEPARATE INT INTO DIGITS
int i=0;
while (num > 0) {
    num1 = (num % (static_cast<ll>(pow(10,i+1))));
    num2 = num1 / static_cast<ll>(pow(10,i));
    num -= num1;
    //NUM2 = extracted digit in this step
    ++i;
}
*/