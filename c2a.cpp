#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v; int temp;
    for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
    sort(v.begin(), v.end());
    if (n == 0) cout << 0 << "\n";
    else {
        int totalcounter = 0;
        int counter = 0;
        int elem = 0;
        for (int i=0; i<n; ++i) {
            if (v[i] != elem) {
                if (counter >= elem) totalcounter += (counter-elem);
                else totalcounter += counter;
                elem = v[i];
                counter = 1;
            }
            else counter++;
        }
        if (counter >= elem) totalcounter += (counter-elem);
        else totalcounter += counter;
        cout << totalcounter << "\n";
    }
    return 0;
}

