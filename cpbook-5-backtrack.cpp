#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void backtrack(vector<bool>& visited, int& pos, const int& n, int& output, int& usedcounter) {
    if (usedcounter == n*n && pos == n*n-1) {++output; return;}
    if (pos == n*n-1) return;
    if (pos % n != n-1 && pos % n != 0 && !visited[pos+1] && !visited[pos-1] &&
        (pos+n >= n*n || visited[pos+n]) && (pos-n < 0 || visited[pos-n])) return;
    if (pos+n < n*n && pos-n >= 0 && !visited[pos+n] && !visited[pos-n] &&
        (pos % n == n-1 || visited[pos+1]) && (pos % n == 0 || visited[pos-1] )) return;
    if (pos != 0 && pos % n != n-1 && !visited[pos+1]) {
        ++pos;
        visited[pos] = true;
        ++usedcounter;
        backtrack(visited, pos, n, output, usedcounter);
        --usedcounter;
        visited[pos] = false;
        --pos;
    }
    if (pos != 0 && pos % n != 0 && !visited[pos-1]) {
        --pos;
        visited[pos] = true;
        ++usedcounter;
        backtrack(visited, pos, n, output, usedcounter);
        --usedcounter;
        visited[pos] = false;
        ++pos;
    }
    if (pos+n < n*n && !visited[pos+n]) {
        pos += n;
        visited[pos] = true;
        ++usedcounter;
        backtrack(visited, pos, n, output, usedcounter);
        --usedcounter;
        visited[pos] = false;
        pos -= n;
    }
    if (pos != 0 && pos-n >= 0 && !visited[pos-n]) {
        pos -= n;
        visited[pos] = true;
        ++usedcounter;
        backtrack(visited, pos, n, output, usedcounter);
        --usedcounter;
        visited[pos] = false;
        pos += n;
    }
}


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int counter = 0;
    vector<bool> visited(n*n, false);
    int pos = 0;
    visited[0] = true;
    int output = 0;
    int usedcounter=1;
    backtrack(visited, pos, n, output, usedcounter);
    cout << output*2 << "\n";


}
