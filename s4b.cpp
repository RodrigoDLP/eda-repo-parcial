#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

bool check(ll& p,  ll& q, ll& r, ll& s, ll& t, ll& u) {

}

ld binary_search(int& target, vector<int>& nums, ld left, ld right) {
    ld lo = left, hi = right;
    for (int loopcounter = 0; loopcounter < 100; ++loopcounter) {
        ld q = lo + (hi-lo)/2.0;
        if (check(nums, q)) hi = q;
        else lo = q;
    } return lo;
}

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int k; cin>> k;
    vector<int> v; int temp;
    for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
    ld maxelem = *max_element(v.begin(), v.end());
    cout << setprecision(10) << binary_search(k, v, 0, maxelem) << "\n";

}
