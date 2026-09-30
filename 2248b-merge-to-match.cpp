#include <bits/stdc++.h>
using namespace std;
typedef long long ll;







int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        bool correct = true;
        int n, m; cin >> n; cin >> m;
        vector<int> nums1, nums2;
        int temp;
        for (int i=0; i<n; ++i) {cin >> temp; nums1.push_back(temp);}
        for (int i=0; i<m; ++i) {cin >> temp; nums2.push_back(temp);}

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for (int i=m-1; i>=0; --i) {
            if (nums1[i+n-m] < nums2[i]) correct = false;

        }


    }
    return 0;
}