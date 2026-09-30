#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct line {
    ll m, b;
    line(ll m=0, ll b=0): m(m), b(b) {}
    ll operator() (const ll& x) {return m*x+b;}
};


int len;
deque<line> CHT;

bool new_is_better(line l1, line l2, line l3) {
    return __int128(l3.b - l1.b) * (l1.m - l2.m) <= __int128(l2.b - l1.b) * (l1.m - l3.m);
}

void add_line(long long m, long long b) {
    line L(m, b);
    while (CHT.size() >= 2 and new_is_better(CHT[len - 2], CHT[len - 1], L)) {
        CHT.pop_back();
        --len;
    }
    CHT.push_back(L);
    ++len;
}

long long query(long long x) {
    while (CHT.size() > 1 and CHT[0](x) > CHT[1](x)) CHT.pop_front();
    len = CHT.size();
    return CHT[0](x);
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, M; cin >> n >> M;


}