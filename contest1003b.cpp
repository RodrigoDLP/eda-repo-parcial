#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll binary_search_sup(vector<ll>& nums, int left, int right, ll& target) {
    if (left == right) {return nums[left];}
    int mid = (left+right)/2;
    if (nums[mid] == target) {return nums[mid];}
    if (nums[mid] > target) return binary_search_sup(nums, left, mid, target);
    return binary_search_sup(nums, mid+1, right, target);
}


ll binary_search_inf(vector<ll>& nums, int left, int right, ll& target) {
    if (left == right) {return nums[left];}
    int mid = (left+right)/2;
    if (nums[mid] == target) {return nums[mid];}
    if (nums[mid] < target) return binary_search_inf(nums, left, mid, target);
    return binary_search_inf(nums, mid+1, right, target);
}


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        ll n, m, j; cin >> n >> m; ll temp;
        vector<ll> nums; for (int i=0; i<n; ++i) {cin>>temp; nums.push_back(temp);}
        vector<ll> nums2; for (int i=0; i<m; ++i) {cin >> temp; nums2.push_back(temp);}
        sort(nums2.begin(), nums2.end());
        vector<ll> nums3; for (int i=nums2.size()-1; i>=0; --i) nums3.push_back(nums2[i]);
        nums[nums.size()-1] = max(nums[nums.size()-1], nums3[0]-nums[nums.size()-1]);
        bool output = true;
        for (int i=nums.size()-1; i>0; --i) {
            ll diff = nums[i-1] - nums[i];
            if (diff > 0) {
                ll target = nums[i-1]+nums[i];
                ll result = binary_search_inf(nums3, 0, nums3.size()-1, target);
                if (result-nums[i-1] > nums[i]) {output = false; break;}
                nums[i-1] = result-nums[i-1];
            } else if (diff < 0) {
                ll target = nums[i-1]+nums[i];
                ll result = binary_search_inf(nums3, 0, nums3.size()-1, target);
                if (result-nums[i-1] <= nums[i] && nums[i-1] <= result-nums[i-1]) nums[i-1] = result-nums[i-1];
            }
        }
        if (output) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main1() {
    vector<ll> nums = {1, 2, 3, 4, 5};
    vector<ll> nums2 = {5, 4, 3, 2, 1};
    ll target = 4;
    cout << binary_search_sup(nums, 0, 3, target);
    cout << binary_search_inf(nums2, 0, 3, target);
}