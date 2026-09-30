#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, int> calculate(vector<int>& nums, int left, int right, int& counter, bool& output) {
    if (!output) return {-1, -1};
    if (right <= left) return make_pair(nums[left], nums[left]);
    if (right - left == 1) {
        if (nums[left] > nums[right]) {++counter; return make_pair(nums[left], nums[right]);}
        return make_pair(nums[right], nums[left]);
    }
    int mid = (left+right)/2;
    auto a1 = calculate(nums, left, mid, counter, output);
    auto a2 = calculate(nums, mid+1, right, counter, output);
    if (a1.first < a2.second) {return make_pair(a2.first, a1.second);}
    if (a2.first < a1.second) {++counter; return make_pair(a1.first, a2.second);}
    output = false; return {-1, -1};
}



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int m; cin >> m;
        vector<int> nums; int temp; for (int i=0; i<m; ++i) {cin>>temp; nums.push_back(temp);}
        bool output = true;
        int counter = 0;
        auto out = calculate(nums, 0, m-1, counter, output);
        if (!output) cout << -1 << "\n";
        else cout << counter << "\n";
    }
}