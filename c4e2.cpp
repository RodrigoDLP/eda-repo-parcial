#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sweep(map<int, int>& av, ll left, ll right, const int& A, const int& B) {
    if (left == right && !av.count(left)) return A;
    auto it = av.lower_bound(left); //Tuve que buscar esto, botaba error al intentar iterar normalmente en map
    ll avcount = 0;
    while (it != av.end() && it->first <= right) {avcount += it->second; ++it;}
    if (avcount == 0) return A;
    if (left == right) return B*avcount;
    ll mid = (left+right)/2;
    avcount *= B * (right-left+1);
    return min(avcount, sweep(av, left, mid, A, B) + sweep(av, mid+1, right, A, B));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, A, B; cin >> n>> k >> A >> B;
    int temp;
    map<int, int> av;
    for (int i=0; i<k; ++i) {
        cin >> temp;
        if (av.count(temp-1)) av[temp-1]++;
        else av[temp-1] = 1;
    }
    ll out = sweep(av, 0, (1<<n)-1, A, B);
    cout << out << "\n";
    return 0;
}