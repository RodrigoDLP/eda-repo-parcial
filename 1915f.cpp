#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void merge(vector<int>& nums, int p, int q, int r) {
    int nL = q-p+1; int nR = r-q;
    vector<int> L(nL); vector<int> R(nR);
    for (int i=0; i<nL; ++i) L[i] = nums[p+i];
    for (int i=0; i<nR; ++i) R[i] = nums[q+i+1];
    int i=0; int j=0; int k = p;
    while (i < nL && j < nR) {
        if (L[i] < R[j]) {nums[k] = L[i]; ++i;}
        else {nums[k] = R[j]; ++j;}
        k++;
    }
    while (i < nL) {nums[k] = L[i]; ++i; ++k;}
    while (j < nR) {nums[j] = R[j]; ++j; ++k;}
}

void merge_sort(vector<int>& nums, int p, int r) {
    if (p >= r) return;
    int q = (p+r)/2;
    merge_sort(nums, p, q);
    merge_sort(nums, q+1, r);
    merge(nums, p, q, r);
}







auto sort1 = [](auto& a, auto& b) {return a.first < b.first;};


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<pair<int, int>> v; int t1, t2;
        for (int i=0; i<n; ++i) {cin >> t1 >> t2; v.emplace_back(t1, t2);}

    }
}