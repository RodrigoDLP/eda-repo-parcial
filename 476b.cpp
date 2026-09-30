#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    cin >> s1 >> s2;
    int plus1=0, plus2=0, minus1=0, minus2=0, unknown=0;
    for (auto c: s1) if (c == '+') ++plus1; else ++minus1;
    for (auto c: s2) if (c == '+') ++plus2; else if (c == '-') ++minus2; else ++unknown;
    int a = plus1-plus2;
    int b = minus1-minus2;
    if (a > unknown || a < 0 || b > unknown || b < 0) {
        cout << setprecision(9) << 0.0 << "\n";
    } else if (unknown == 0) cout << setprecision(9) << 1.0 << "\n";
    else {
        double current = 1;
        for (int i=max(a, b)+1; i<=unknown; ++i) current *= i;
        for (int i=2; i<=min(a, b); ++i) current /= i;
        double result = current/(1<<unknown);
        cout << setprecision(9) << result << "\n";
    }
}