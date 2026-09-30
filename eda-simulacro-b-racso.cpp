#include <bits/stdc++.h>
using namespace std;

const int L = 100000 + 20;

template<int B = 311, int MOD = 1000000007>
struct SubstringHash {
    int hash_1;
    int power_1;
    SubstringHash(int hash_1 = 0, int power_1 = B) : hash_1(hash_1), power_1(power_1) {};

    SubstringHash operator + (const SubstringHash &rhs) const {
        SubstringHash result;
        result.hash_1 = (1ll * hash_1 * rhs.power_1 + rhs.hash_1) % MOD;
        result.power_1 = (1ll * power_1 * rhs.power_1) % MOD;
        return result;
    }

    bool operator == (const SubstringHash &rhs) const {
        return hash_1 == rhs.hash_1;
    }
};

struct PersistentSegmentTreeNode {
    int value;
    int l, r;
    SubstringHash<> segment_hash;
    PersistentSegmentTreeNode* left;
    PersistentSegmentTreeNode* right;

    PersistentSegmentTreeNode(int l = 0, int r = L - 1, int value = 0, SubstringHash<> segment_hash = SubstringHash(), PersistentSegmentTreeNode* left = nullptr, PersistentSegmentTreeNode* right = nullptr) : l(l), r(r), value(value), segment_hash(segment_hash),  left(left), right(right) {}

    void build(int c) {
        if (l == r) {
            value = c;
            segment_hash = SubstringHash(c + 1);
            return;
        }
        int mi = (l + r) / 2;
        left = new PersistentSegmentTreeNode(l, mi);
        right = new PersistentSegmentTreeNode(mi + 1, r);
        left -> build(c);
        right -> build(c);
        value = right -> value + left -> value;
        segment_hash = right -> segment_hash + left -> segment_hash;
    }

    bool operator == (const PersistentSegmentTreeNode &rhs) const {
        return segment_hash == rhs.segment_hash;
    }

    bool operator < (const PersistentSegmentTreeNode &rhs) const {
        const PersistentSegmentTreeNode *L = this;
        const PersistentSegmentTreeNode *R = &rhs;
        while (L -> l != L -> r) {
            if (L -> right -> segment_hash != R -> right -> segment_hash) {
                L = L -> right;
                R = R -> right;
            }
            else {
                L = L -> left;
                R = R -> left;
            }
        }
        return L -> value < R -> value;
    }

    bool operator > (const PersistentSegmentTreeNode &rhs) {
        return rhs < *this;
    }
};

struct Compare {
    bool operator() (const pair<PersistentSegmentTreeNode*, int>& a, const pair<PersistentSegmentTreeNode*, int>& b) const {
        return *b.first < *a.first;
    }
};

struct BigIntegerVersionController {
    vector<PersistentSegmentTreeNode*> roots;
    BigIntegerVersionController() {
        roots.emplace_back(new PersistentSegmentTreeNode());
        roots.back() -> build(0);
        roots.emplace_back(new PersistentSegmentTreeNode());
        roots.back() -> build(1);
    }

    void set_to_value(PersistentSegmentTreeNode *prev, PersistentSegmentTreeNode *cur, PersistentSegmentTreeNode* val, int x, int y) {
        int l = cur -> l;
        int r = cur -> r;
        int mi = (l + r) / 2;
        if (x <= l and mi <= y) {
            cur -> left = val -> left;
        }
        else if (y < l or mi < x) {
            cur -> left = prev -> left;
        }
        else {
            cur -> left = new PersistentSegmentTreeNode(l, mi);
            set_to_value(prev -> left, cur -> left, val -> left, x, y);
        }
        if (x <= mi + 1 and r <= y) {
            cur -> right = val -> right;
        }
        else if (y < mi + 1 or r < x) {
            cur -> right = prev -> right;
        }
        else {
            cur -> right = new PersistentSegmentTreeNode(mi + 1, r);
            set_to_value(prev -> right, cur -> right, val -> right, x, y);
        }
        cur -> value = cur -> right -> value + cur -> left -> value;
        cur -> segment_hash = cur -> right -> segment_hash + cur -> left -> segment_hash;
    }

    int query_position(int version, int x) {
        PersistentSegmentTreeNode* root = roots[version];
        while (root -> l != root -> r) {
            int mi = (root -> l + root -> r) / 2;
            if (x <= mi) {
                root = root -> left;
            }
            else {
                root = root -> right;
            }
        }
        return root -> value;
    }

    int get_nxt_zero(PersistentSegmentTreeNode *root, int x) {
        if (root -> r < x) return -1;
        if (root -> r - root -> l + 1 == root -> value) return -1;
        if (root -> l == root -> r) {
            assert(root -> value == 0);
            return root -> l;
        }
        int left_value = get_nxt_zero(root -> left, x);
        if (left_value == -1) return get_nxt_zero(root -> right, x);
        return left_value;
    }

    int add(int version, int x) {
        if (query_position(version, x)) {
            int to = get_nxt_zero(roots[version], x);
            roots.emplace_back(new PersistentSegmentTreeNode(0, L - 1, roots[version] -> value, roots[version] -> segment_hash, roots[version] -> left, roots[version] -> right));
            set_to_value(roots[version], roots.back(), roots[0], x, to - 1);
            roots.emplace_back(new PersistentSegmentTreeNode(0, L - 1, roots.back() -> value, roots.back() -> segment_hash, roots.back() -> left, roots.back() -> right));
            set_to_value(roots[(int)roots.size() - 2], roots.back(), roots[1], to, to);
        }
        else {
            roots.emplace_back(new PersistentSegmentTreeNode(0, L - 1, roots[version] -> value, roots[version] -> segment_hash, roots[version] -> left, roots[version] -> right));
            set_to_value(roots[version], roots.back(), roots[1], x, x);
        }
        return (int)roots.size() - 1;
    }

    bool is_smaller(const int &v1, const int &v2) {
        return *roots[v1] < *roots[v2];
    }
};

const int N = 100000 + 5;

int n;
int m;
int D[N];
int par[N];
bool vis[N];
vector<pair<int, int>> G[N];

void Dijkstra(int src, int snk) {
    memset(D, -1, sizeof D);
    BigIntegerVersionController controller;
    D[src] = 0;
    priority_queue<pair<PersistentSegmentTreeNode*, int>, vector<pair<PersistentSegmentTreeNode*, int>>, Compare> Q;
    Q.emplace(controller.roots[0], src);
    while (not Q.empty()) {
        int u;
        PersistentSegmentTreeNode* cur;
        tie(cur, u) = Q.top(); Q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &e : G[u]) {
            int v, x;
            tie(v, x) = e;
            int new_value = controller.add(D[u], x);
            if (D[v] == -1 or controller.is_smaller(new_value, D[v])) {
                D[v] = new_value;
                par[v] = u;
                Q.emplace(controller.roots[D[v]], v);
            }
        }
    }
    if (D[snk] == -1) {
        cout << -1 << '\n';
        return;
    }
    const int MOD = 1e9 + 7;
    int res = 0;
    int p = 1;
    for (int i = 0; i < L; ++i) {
        if (controller.query_position(D[snk], i)) {
            res += p;
        }
        if (res >= MOD) res -= MOD;
        p <<= 1;
        if (p >= MOD) p -= MOD;
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    int s, t;
    cin >> s >> t;
    Dijkstra(s, t);
    if (D[t] == -1) {
        return 0;
    }
    int at = t;
    vector<int> path;
    while (at != s) {
        path.emplace_back(at);
        at = par[at];
    }
    path.emplace_back(s);
    reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << " \n"[i + 1 == path.size()];
    }
    return 0;
}