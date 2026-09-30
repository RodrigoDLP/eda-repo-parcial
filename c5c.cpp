#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m, temp; cin>> n >> m; ll c = 0;
        vector<int> nums(n, 0);
        for (int i=0; i<n; ++i) {
            cin >> temp;
            nums[i] = temp;
        }
        ll currentsum = 0;
        priority_queue<pair<int, int>> pq; //pq.push(make_pair(nums[m-1], m));
        //if (currentsum > 0) {nums[m-1] = -nums[m-1]; pq.pop(); pq.push(make_pair(nums[m-1], m)); currentsum *= -1; ++c;}
        for (int i=m; i>=2; --i) {
            pq.push(make_pair(nums[i-1], i));
            currentsum += nums[i-1];
            if (currentsum > 0) {
                //cout << "currentsum before: " << currentsum << " -- ";
                auto p = pq.top();
                currentsum -= 2 * p.first;
                nums[p.second-1] = -1 * nums[p.second-1];
                pq.pop();
                pq.push(make_pair(nums[p.second-1], p.second));
                ++c;
                //cout << "augmenting c for i=" << i << "\n";
            }
        }
        auto lambda1 = [](auto& a1, auto& a2){return a1.first > a2.first;};
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(lambda1)> pq2(lambda1);
        currentsum = 0;
        for (int i=m+1; i<=n; ++i) {
            pq2.push(make_pair(nums[i-1], i));
            currentsum += nums[i-1];
            if (currentsum < 0) {
                //cout << "currentsum2 before: " << currentsum << " -- ";
                auto p = pq2.top();
                currentsum -= 2 * p.first;
                nums[p.second-1] = -1 * nums[p.second-1];
                pq2.pop();
                pq2.push(make_pair(nums[p.second-1], p.second));
                ++c;
                //cout << "augmenting c for i=" << i << "\n";
            }
        }
        cout << c << "\n";
    }
}