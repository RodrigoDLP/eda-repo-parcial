#include <bits/stdc++.h>
#include <numeric>
using namespace std;
typedef long long ll;
ll gcf(ll a, ll b) {
    if (b > a ) swap(a, b);
    if (b == 1) return 1;
    if (a % b == 0) return b;
    int c = gcf(a, a%b);
    int d = gcf(b, a%b);
    return gcf(c, d);
}


int main() {
    //cout << gcf(12342472, 4096) << endl;
    ll a = 1e16;
    ll b = 1e14;
    int ac = gcd(a, b);
    cout << ac << "\n";
}