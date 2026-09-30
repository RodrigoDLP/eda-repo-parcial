#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


bool valid(vector<int>& bamboo, int& a, int& b, int& c) {
    bool afound = false, bfound = false, cfound = false;
    for (auto& e: bamboo) {
        if (e == a) afound = true;
        if (e == b) bfound = true;
        if (e == c) cfound = true;
    }
    return afound && bfound && cfound;
}

void backtrack(int& mp, vector<int>& bamboo, ll& optimal, int& a, int& b, int& c, vector<int>& deleteornot) {
    if (optimal != -1 && mp > optimal) return;
    if (valid(bamboo, a, b, c)) {optimal = mp; return;}
    for (int i=0; i<bamboo.size(); ++i) {
        if (bamboo[i] != 1 && deleteornot[i] % 3 == 0) {
            bamboo[i]--;
            mp++;
            int prev = deleteornot[i];
            deleteornot[i] = 3;
            backtrack(mp, bamboo, optimal, a, b, c, deleteornot);
            deleteornot[i] = prev;
            mp--;
            bamboo[i]++;
        }
        if (bamboo[i] > max({a, b, c})) continue;
        if (bamboo[i] < max({a, b, c}) && deleteornot[i] != 3) {
            bamboo[i]++;
            mp++;
            int prev = deleteornot[i];
            deleteornot[i] = 2;
            backtrack(mp, bamboo, optimal, a, b, c, deleteornot);
            deleteornot[i] = prev;
            mp--;
            bamboo[i]--;
        }
        if (deleteornot[i] <= 1 && i < bamboo.size()-1) {
            for (int j=i+1; j<bamboo.size(); ++j) {
                if (bamboo[j] > max({a, b, c})) continue;
                int originalj = bamboo[j];
                bamboo[j] = bamboo[bamboo.size()-1];
                bamboo[i] += originalj;
                bamboo.pop_back();
                mp+=10;
                int prev = deleteornot[i];
                deleteornot[i] = 1;
                backtrack(mp, bamboo, optimal, a, b, c, deleteornot);
                deleteornot[i] = prev;
                mp-=10;
                bamboo[i] -= originalj;
                if (j < bamboo.size()) {
                    bamboo.push_back(bamboo[j]);
                    bamboo[j] = originalj;
                }
                else bamboo.push_back(originalj);
            }
        }
    }

}

// <>, <<, >>
int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int mp = 0;
    ll optimal = -1;
    int a, b, c;
    int n; cin >> n; cin>>a>>b>>c;
    int temp;
    vector<int> deleteornot;
    vector<int> bamboo;
    for (int i=0; i<n; ++i) {cin>>temp; bamboo.push_back(temp);}
    cout << "start\n";
    backtrack(mp, bamboo, optimal, a, b, c, deleteornot);
    cout << optimal << "\n";
}
