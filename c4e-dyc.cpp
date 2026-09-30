#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


ll sweep(unordered_map<int, int>& av, int left, int right, const int& A, const int& B) {
    if (left == right && !av.count(left)) return A;
    ll avcount = accumulate(av.begin(), av.end(), 0, [&](auto sum, auto a){if (a.first >= left && a.first <= right) return sum + a.second; return sum;});
    //ll avcount = 0;
    //for (int i=left; i<=right; ++i) {if (av.count(i)) avcount += av[i];}
    if (avcount == 0) {//cout << "min for " << left << ":" << right << " is " << A << "\n";
        return A;}
    if (left == right) {//cout << "min for " << left << ":" << right << " is " << B*avcount << "\n";
        return B*avcount; }
    int mid = (left+right)/2;
    avcount *= B * (right-left+1);
    return min((ll)(avcount), sweep(av, left, mid, A, B) + sweep(av, mid+1, right, A, B));
    //cout << "min for " << left << ":" << right << " is " << out << "\n";
}











// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, A, B; cin >> n>> k >> A >> B;
    int temp; //vector<int> av(1<<n, 0);
    unordered_map<int, int> av;
    for (int i=0; i<k; ++i) {
        cin >> temp;
        if (av.count(temp-1)) av[temp-1]++;
        else av[temp-1] = 1;
    }
    ll out = sweep(av, 0, (1<<n)-1, A, B);
    cout << out << "\n";
    return 0;
}