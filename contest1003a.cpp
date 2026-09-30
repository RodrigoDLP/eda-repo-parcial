#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        ll n, m, j; cin >> n >> m; ll temp;
        vector<ll> nums; for (int i=0; i<n; ++i) {cin>>temp; nums.push_back(temp);}
        cin >> j;
        nums[nums.size()-1] = max(nums[nums.size()-1], j-nums[nums.size()-1]);
        bool output = true;

        for (int i=nums.size()-1; i>0; --i) {
                if (nums[i-1] <= nums[i] && j-nums[i-1] <= nums[i]) {nums[i-1] = max(nums[i-1], j-nums[i-1]);}
                else if (nums[i-1] <= nums[i]) {}
                else if (j-nums[i-1] <= nums[i]) {nums[i-1] = j-nums[i-1];}
                else {output = false; break;}
        }
        if (output) cout << "YES\n";
        else cout << "NO\n";
    }
}