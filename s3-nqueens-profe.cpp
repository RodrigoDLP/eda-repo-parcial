#include <bits/stdc++.h>
using namespace std;

const int n = 15;

int f(int col, vector<bool> &rows, vector<bool> &diag1, vector<bool> &diag2) {
    if (col == n) {
        return 1;
    }
    int res = 0;
    for (int row = 0; row < n; ++row) {
        if (rows[row]) continue;
        if (diag1[row + col]) continue;
        if (diag2[row - col + (n - 1)]) continue;
        rows[row] = true;
        diag1[row + col] = true;
        diag2[row - col + (n - 1)] = true;
        res += f(col + 1, rows, diag1, diag2);
        rows[row] = false;
        diag1[row + col] = false;
        diag2[row - col + (n - 1)] = false;
    }
    return res;
}

int main() {
    vector<bool> rows(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
    cout << f(0, rows, diag1, diag2) << '\n';
    return 0;
}


/*
for (int mask = 0; mask < (1 << n); mask++) {
vector<int> subconjunto;
for (int i = 0; i < n; i++)
if (mask & (1 << i))
subconjunto.push_back(a[i]);
// procesar "subconjunto"
}





*/