#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef float ld;

bool ans_greater(ld x, vector<int>& nums) {
    ld ans = nums[0] * exp(-x) + nums[1] * sin(x) + nums[2] * cos(x) + nums[3] * tan(x) + nums[4] *x*x + nums[5];
    return (ans > 0);
}

bool ans_lower(ld x, vector<int>& nums) {
    ld ans = nums[0] * exp(-x) + nums[1] * sin(x) + nums[2] * cos(x) + nums[3] * tan(x) + nums[4] *x*x + nums[5];
    return (ans < -1e-6);
}


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        vector<int> nums(6);

        while (cin >> nums[0] >> nums[1] >> nums[2] >> nums[3] >> nums[4] >> nums[5]) {
            //cout << "HI\n";
            if (ans_lower(0, nums) || ans_greater(1, nums)) {cout << "No solution\n"; continue;}
            ld lo=0.0, hi=1.0;
            for (int i=0; i<200; ++i) {
                ld mi = lo + (hi-lo)/2;
                if (ans_greater(mi, nums)) lo = mi; else hi = mi;
            }
            cout << setprecision(16) << hi << "\n";
        }
    return 0;
}