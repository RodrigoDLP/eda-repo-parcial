#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main1() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<string> nums; string temp;
    vector<pair<int, int>> diffs;
    for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}
    for (int i=0; i<k; ++i) {
        int maxlocal=-1, minlocal=10;
        for (int j=n; j<n; ++j) {
            if (stoi(string(1, nums[j][i])) > maxlocal) maxlocal = stoi(string(1, nums[j][i]));
            if (stoi(string(1, nums[j][i])) < minlocal) minlocal = stoi(string(1, nums[j][i]));
        }
        diffs.emplace_back(i, maxlocal-minlocal);
    }
    auto sortsecond = [](const auto& a, const auto& b){return a.second < b.second;};
    sort(diffs.begin(), diffs.end(), sortsecond);
    int minindex = -1, minnum = 10;
    for (int index=0; index<k; ++index) {
        int realindex = diffs[index].first;
        int maxlocal1=-1, minlocal1 = 10;
        for (int i=0; i<n; ++i) {
            if (nums[i][realindex] > maxlocal1) maxlocal1 = nums[i][realindex];
            if (nums[i][realindex] < minlocal1) minlocal1 = nums[i][realindex];
        }
    }








}
/*

bool mega_next_permutation(vector<string>& a) {
    for (int i=0; i<a.size(); ++i) {
        if (!next_permutation(a[i].begin(), a[i].end())) return false;
    }
    return true;
}
*/

void apply_permutation(string& s, const string& original, vector<int>& v) {
    string result;
    for (int i=0; i<v.size(); ++i) result += original[v[i]];
    s = result;
}

int maxmindiff(vector<string>& a, const vector<string>& aoriginal, vector<int>& indexes) {
    int max = -1, min=INT_MAX;
    for (int i=0; i<a.size(); ++i) {
        apply_permutation(a[i], aoriginal[i], indexes);
    }
    for (int i=0; i<a.size(); ++i) if (stoi(a[i]) > max) max = stoi(a[i]);
    for (int i=0; i<a.size(); ++i) if (stoi(a[i]) < min) min = stoi(a[i]);
    return max-min;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<string> nums;
    vector<string> nums2;
    vector<int> indexes(k); string temp;
    for (int i=0; i<k; ++i) indexes[i] = i;
    int minmaxmindiff = INT_MAX;
    for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}
    copy(nums.begin(), nums.end(), back_inserter(nums2));
    do {
        int a = maxmindiff(nums2, nums, indexes);
        if (a < minmaxmindiff) minmaxmindiff = a;
    } while (next_permutation(indexes.begin(), indexes.end()));
    cout << minmaxmindiff << "\n";




}