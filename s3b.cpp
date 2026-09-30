#include <numeric>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int gcf(int a, int b) {
    if (b > a) swap(a, b);
    if (b == 1) return 1;
    if (a % b == 0) return b;
    int c = gcf(a, a%b);
    int d = gcf(b, a%b);
    return gcf(c, d);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<ll> nums; ll temp;
        for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}
        if (n == 1) {cout << temp << "\n";}
        else cout << gcd(nums[0], nums[nums.size()-1]) << "\n";
    }
}