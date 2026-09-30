#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
int valid(vector<int>& nums) {
    int maxstate = 2;
    ll a = nums[0] + nums[1] + nums[3] + nums[4];
    ll b = nums[1] + nums[2] + nums[4] + nums[5];
    ll c = nums[3] + nums[4] + nums[6] + nums[7];
    ll d = nums[4] + nums[5] + nums[7] + nums[8];
    if (a < 0 || b < 0 || c < 0 || d < 0) maxstate = 1;
    if (!((a == b || a < 0 || b < 0) && (c == d || c < 0 || d < 0) && (a == c || a < 0 || c < 0))) maxstate = 0;
    return maxstate;
}



void backtrack(vector<int>& nums, int& counter) {
    if (valid(nums) == 2) ++counter;
    if (valid(nums) == 0) return;
    for ()
    backtrack(nums, counter);

}
*/




// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> nums(9, 0);
    ll n; cin >> n;
    int temp;
    cin >> temp; nums[1] = temp;
    cin >> temp; nums[3] = temp;
    cin >> temp; nums[5] = temp;
    cin >> temp; nums[7] = temp;
    int a1 = nums[1] + nums[3], a2 = nums[1] + nums[5], a3 = nums[7] + nums[3], a4 = nums[7] + nums[5];
    int a = max({a1, a2, a3, a4});
    int b = min({a1, a2, a3, a4});
    if (a-b<=n) cout << (n-(a-b))*n << "\n";
    else cout << 0 << "\n";
}