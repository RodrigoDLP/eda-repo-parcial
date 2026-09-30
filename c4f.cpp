#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int g(vector<int>& a, int i, int j) {
    int sum = 0;
    for (int k = min(i, j) + 1; k <= max(i, j); k = k + 1)
        sum = sum + a[k];
    return sum;
}





// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, temp; cin >> n;
    vector<int> v; for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}

}
