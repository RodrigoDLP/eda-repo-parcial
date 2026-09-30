#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n; int temp;
        vector<int> nums;
        for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}

        if (n % 2 == 1) {
            for (int i=1; i<nums.size(); ++i) {if (nums[0])}
            cout << 8 << "\n" << 1 << " " << n << 1 << " " << n-1 << "\n";
        }
        if (n % 2 == 0) {
            cout << 4 << "\n" << 1 << " " << n << "\n" << 1 << " " << n << "\n";
        }
    }
}