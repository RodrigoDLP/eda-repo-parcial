#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


/*void backtrack2(vector<int>& v, int& a, int& b, int& c, int& mp, int& best, vector<int>& action) {
    if (valid(v, a, b, c) && mp < best) {best = mp; return;}
    if (mp > best && best != -1) return;
    for (int i=0; i<v.size(); ++i) {
        if (action[i] == 1 && v[i] <= max({a, b, c})) {
            mp++; v[i]++;
            backtrack2(v, a, b, c, mp, best, action);
            v[i]--; mp--;
        } else if (action[i] == 2 && v[i] > 1) {
            mp++; v[i]--;
            backtrack2(v, a, b, c, mp, best, action);
            v[i]++; mp--;
        } else {
            mp++;
            if (v[i] <= max({a, b, c})) {
                v[i]++; action[i] = 1;
                backtrack2(v, a, b, c, mp, best, action);
                v[i]--; action[i] = 0;
            }
            if (v[i] > 1) {
                v[i]--; action[i] = 2;
                backtrack2(v, a, b, c, mp, best, action);
                v[i]++; action[i] = 0;
            }
            mp--;
        }
    }
}
bool valid(vector<int>& bamboo, int& a, int& b, int& c) {
    bool afound = false, bfound = false, cfound = false;
    for (auto& e: bamboo) {
        if (e == a) afound = true;
        if (e == b) bfound = true;
        if (e == c) cfound = true;
    }
    return afound && bfound && cfound;
}

auto sort1 = [](auto& a, auto& b){return get<1>(a) < get<1>(b);};
auto sort2 = [](auto& a, auto& b){return get<2>(a) < get<2>(b);};
auto sort3 = [](auto& a, auto& b){return get<3>(a) < get<3>(b);};
*/

ll combined_distance(vector<int>& v, int& a, int& b, int& c) {
    vector<int> distsa, distsb, distsc;

    for (int i=0; i<v.size(); ++i) distsa.emplace_back(abs(a-v[i]));
    for (int i=0; i<v.size(); ++i) distsb.emplace_back(abs(b-v[i]));
    for (int i=0; i<v.size(); ++i) distsc.emplace_back(abs(c-v[i]));
    ll bestdist = -1;
    //cout << "called on v.size=" << v.size() <<"\n";
    for (int a1 = 0; a1 < v.size(); ++a1) {
        for (int b1 = 0; b1 < v.size(); ++b1) {
            if (a1 == b1) continue;
            for (int c1 = 0; c1 < v.size(); ++c1) {
                if (a1 == c1 || b1 == c1) continue;
                if (bestdist == -1 || distsa[a1] + distsb[b1] + distsc[c1] < bestdist) bestdist = distsa[a1] + distsb[b1] + distsc[c1];
            }
        }
    }
    //if (bestdist  == -1) cout << "something is happening\n";
    return bestdist;
}



void backtrack1(vector<int>& v, int& a, int& b, int& c, int& mp, int& best, vector<int>& action) {
    if (v.size() < 3) return;
    if (best == -1 || mp+combined_distance(v, a, b, c) < best) best = mp+combined_distance(v, a, b, c);
    if (mp > best && best != -1) return;
    for (int i=0; i<v.size()-1; ++i) {
        for (int j=i+1; j<v.size(); ++j) {
            if (max(v[i], v[j]) > max({a, b, c})) continue;
            if (mp + 10 > best) continue;
            if (mp > best && best != -1) return;
            int sacrificed = v[j];
            swap(v[j], v[v.size()-1]);
            v.pop_back();
            v[i] += sacrificed;
            mp += 10;
            backtrack1(v, a, b, c, mp, best, action);
            mp -= 10;
            v[i] -= sacrificed;
            v.push_back(sacrificed);
            swap(v[j], v[v.size()-1]);
        }
    }
}





// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b, c; cin >> n >> a >> b >> c;
    vector<int> v; int temp; for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
    vector<int> action(v.size(), 0);
    int best = -1; int mp = 0;
    backtrack1(v, a, b, c, mp, best, action);
    cout << best << "\n";
}
