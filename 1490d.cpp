#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void iter(const vector<int>& nums, int left, int right, int depth, unordered_map<int, int>& depths) {
    //cout << "loop left=" << left << " right=" << right << "\n";
    if (left > right) return;
    if (left == right) {
        depths[nums[left]] = depth; return;
    }
    int i = left; int maxf = -1; int maxi = -1;

    while (i <= right) {
        if (nums[i] > maxf) {
            maxf = nums[i]; maxi = i;
        }
        ++i;
    }
    //cout << "maxf=" << maxf << "\n";
    //cout << "hi\n";
    //if (maxi == -1) cout << "negativeone\n";
    depths[nums[maxi]] = depth;
    iter(nums, left, maxi-1, depth+1, depths);
    iter(nums, maxi+1, right, depth+1, depths);
}



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        unordered_map<int, int> depths;
        int n; cin >> n;
        //cout << "?\n";
        int temp; vector<int> v; for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        //cout << "?\n";
        iter(v, 0, n-1, 0, depths);
        for (int i=0; i<n; ++i) cout << depths[v[i]] << " "; cout << "\n";
    }
}