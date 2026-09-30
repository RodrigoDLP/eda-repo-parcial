#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void backtrack(vector<vector<int>>& output, const vector<int>& nums, vector<int>& current, unordered_map<int, int>& used, int& level, const vector<int>& lastindex) {
    if (level == nums.size()) {output.push_back(current); return;}
    for (int i=0; i<nums.size(); ++i) {
        if (used[nums[i]] == 0 || lastindex[i] - i != used[nums[i]] - 1) continue;
        used[nums[i]]--;
        current.push_back(nums[i]);
        ++level;
        backtrack(output, nums, current, used, level, lastindex);
        --level;
        current.pop_back();
        used[nums[i]]++;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    unordered_map<int, int> remaining_uses;
    vector<int> current;
    vector<vector<int>> output;
    vector<int> snums = nums;
    sort(snums.begin(), snums.end());
    vector<int> lastindex(nums.size(), 0);
    remaining_uses[snums[snums.size()-1]] = 1;
    lastindex[nums.size()-1] = nums.size()-1;
    for (int i=snums.size()-2; i>=0; --i) {
        if (snums[i] != snums[i+1]) {
            lastindex[i] = i;
        } else lastindex[i] = lastindex[i+1];
        if (remaining_uses.count(snums[i])) remaining_uses[snums[i]]++;
        else remaining_uses[snums[i]] = 1;
    }
    int level = 0;
    backtrack(output, snums, current, remaining_uses, level, lastindex);
    return output;
}

vector<string> calculateDots(int remaining, int startindex, int& iplength, vector<int>& v) {
    if (remaining * 3 < iplength-startindex) return {};
    if (v[startindex] == 0) return calculateDots(remaining-1, startindex+1, iplength, v);
    vector<string> out1 = calculateDots(remaining-1, startindex+1, iplength, v);
    vector<string> out2 = (v[startindex] != 0) ? calculateDots(remaining-1, startindex+2, iplength, v) : {};
    vector
}









// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; vector<int> a; int temp;
    for (int i=0; i<n; ++i) {cin >> temp; a.push_back(temp);}
    vector<vector<int>> conjuntos = permuteUnique(a);
    vector<vector<int>> conjuntos2(conjuntos.size());
    for (auto v: conjuntos) {
        conjuntos2.push_back(v);
    }
    for (auto v: conjuntos) {
        for (int i=v.size()-2; i>=0; ++i) v.push_back(v[i]);
    }
    for (auto v: conjuntos2) {
        for (int i=v.size()-1; i>=0; ++i) v.push_back(v[i]);
    }



















}