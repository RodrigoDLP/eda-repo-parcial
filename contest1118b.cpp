#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void insert_vector_at_index(vector<int>& src, vector<int>& dest, int& index) {
    vector<int> temp; temp.reserve(dest.size()-index);
    for (int i=index; i<dest.size(); ++i) temp.push_back(dest[i]);
    if (index+src.size() < dest.size()) {
        int indexplussrc = index+src.size();
        for (int i=index; i<indexplussrc; ++i) dest[i] = src[i-index];
        for (int i=indexplussrc; i<dest.size(); ++i) dest[i] = temp[i-indexplussrc];
        for (int i=dest.size(); i<dest.size()+src.size(); ++i) dest.push_back(temp[i-indexplussrc]);
    } else {
        for (int i=index; i<dest.size(); ++i) dest[i] = src[i-index];
        for (int i=dest.size(); i<index+src.size(); ++i) dest.push_back(src[i-index]);
        for (int i : temp) dest.push_back(i);
    }
}

void fill_with_value(vector<int>& v, int value, int amount) {
    for (int i=0; i<amount; ++i) v.push_back(value);
}



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        int lastanswer = -1;
        bool repeat = false;
        deque<int> numsoriginal; int temp;
        for (int i=0; i<n; ++i) {cin >> temp; numsoriginal.push_back(temp);}
        sort(numsoriginal.begin(), numsoriginal.end());
        deque<int> nums; copy(numsoriginal.begin(), numsoriginal.end(), back_inserter(nums));
        int index = 0;
        int lowerindex = 0;
        int count = 0;
        int maxcount = 0;
        int bestcutter = -1;
        int bestlowerindex = -1;
        int bestoldindex = -1;
        for (int i=1; i<=m; ++i) {
            if (repeat) {cout << lastanswer << " "; continue;}
            for (int ii = 0; ii<i; ++ii) {
                nums.clear();
                copy(numsoriginal.begin(), numsoriginal.end(), back_inserter(nums));
                while (index < nums.size()) {
                    int current = nums[index];
                    while (nums[lowerindex] < current / 2) ++lowerindex;
                    count += nums.size()-lowerindex;
                    int oldindex = index;
                    while (index < nums.size() && nums[index] == current) {++index;}
                    if (current % 2 == 0) count += index-oldindex;
                    if (count > maxcount) {maxcount = count; bestcutter = current/2; bestlowerindex = lowerindex; bestoldindex = oldindex;}
                    count = 0;
                }
            }
            cout << maxcount << " ";
            if (lastanswer == maxcount) repeat = true;
            int currentnumssize = nums.size();
            for (int j=bestlowerindex; j<currentnumssize; ++j) {nums.push_back(bestcutter); nums[j] -= bestcutter;}
            sort(nums.begin(), nums.end());
            while (nums[0] == 0) nums.pop_front();
        } cout << "\n";
    }
}