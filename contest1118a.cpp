#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> nums; int temp;
        for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}
        sort(nums.begin(), nums.end());
        int index = 0;
        int lowerindex = 0;
        int count = 0;
        int maxcount = 0;

        while (index < n) {
            int current = nums[index];
            while (nums[lowerindex] < current / 2) ++lowerindex;
            count += n-lowerindex;
            int oldindex = index;
            while (index < n && nums[index] == current) {++index;}
            if (current % 2 == 0) count += index-oldindex;
            if (count > maxcount) maxcount = count;
            count = 0;
        }
        cout << maxcount << "\n";
    }
}