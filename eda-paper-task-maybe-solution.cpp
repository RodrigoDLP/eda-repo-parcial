#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    ============================================================
    Persistent Segment Tree
    ============================================================

    Se conserva la estructura que proporcionaste.

    En esta solución no necesitamos usarlo para la consulta final,
    porque guardar n versiones de un PST para los balances consumiría
    O(n log n) nodos (~10 millones para n=500000).

    En su lugar usamos vectores de posiciones por cada valor del
    balance, lo que permite contar ocurrencias con binary search.
*/
template<typename data_type>
struct PersistentSegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;

        SegmentTreeNode(
            data_type data,
            int l,
            int r,
            SegmentTreeNode* left,
            SegmentTreeNode* right
        ) : data(data), l(l), r(r), left(left), right(right) {}
    };

    vector<SegmentTreeNode*> version_roots;

    PersistentSegmentTree(int n) {
        version_roots.emplace_back(
            new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr)
        );
        build(version_roots[0]);
    }

    PersistentSegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(
            new SegmentTreeNode(data_type(), l, r, nullptr, nullptr)
        );
        build(version_roots[0], a);
    }

    void build(SegmentTreeNode *root) {
        if (root->l == root->r) {
            root->data = data_type();
            return;
        }

        int mi = (root->l + root->r) / 2;

        root->left = new SegmentTreeNode(
            data_type(), root->l, mi, nullptr, nullptr
        );

        root->right = new SegmentTreeNode(
            data_type(), mi + 1, root->r, nullptr, nullptr
        );

        build(root->left);
        build(root->right);
    }

    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root->l == root->r) {
            root->data = a[root->l - 1];
            return;
        }

        int mi = (root->l + root->r) / 2;

        root->left = new SegmentTreeNode(
            data_type(), root->l, mi, nullptr, nullptr
        );

        root->right = new SegmentTreeNode(
            data_type(), mi + 1, root->r, nullptr, nullptr
        );

        build(root->left, a);
        build(root->right, a);
    }

    void update(
        int pos,
        data_type value,
        SegmentTreeNode *last,
        SegmentTreeNode *curr
    ) {
        if (curr->l == curr->r) {
            curr->data = value;
            return;
        }

        int mi = (curr->l + curr->r) / 2;

        if (pos <= mi) {
            curr->right = last->right;

            curr->left = new SegmentTreeNode(
                last->left->data,
                curr->l,
                mi,
                nullptr,
                nullptr
            );

            update(pos, value, last->left, curr->left);
        }
        else {
            curr->left = last->left;

            curr->right = new SegmentTreeNode(
                last->right->data,
                mi + 1,
                curr->r,
                nullptr,
                nullptr
            );

            update(pos, value, last->right, curr->right);
        }

        curr->data = curr->left->data + curr->right->data;
    }

    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(
            data_type(),
            version_roots[0]->l,
            version_roots[0]->r,
            nullptr,
            nullptr
        );

        version_roots.emplace_back(root);

        update(pos, value, version_roots[version], root);

        return (int)version_roots.size() - 1;
    }

    data_type query(
        int x,
        int y,
        SegmentTreeNode *root
    ) {
        if (y < root->l || root->r < x || x > y)
            return data_type(0);

        if (x <= root->l && root->r <= y)
            return root->data;

        return query(x, y, root->left)
             + query(x, y, root->right);
    }

    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }

    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};


/*
    ============================================================
    Suffix Array
    ============================================================

    O(n log n) con doubling + counting sort.
*/
struct SuffixArray {
    int n;
    string s;

    vector<int> sa;      // suffix array
    vector<int> rank_;   // rank_[pos]
    vector<int> lcp;    // lcp[i] = LCP(sa[i], sa[i-1])

    SuffixArray(const string& str) {
        s = str;
        n = (int)s.size();

        build_sa();
        build_lcp();
    }

    void build_sa() {
        sa.resize(n);
        rank_.resize(n);

        vector<int> tmp(n);
        vector<int> sa2(n);

        // Initial ranks: '(' < ')'
        for (int i = 0; i < n; ++i) {
            rank_[i] = (s[i] == '(' ? 0 : 1);
            sa[i] = i;
        }

        for (int k = 1;; k <<= 1) {
            /*
                Radix/counting sort por:
                    (rank[i], rank[i+k])
            */

            int classes = max(n, 2) + 2;

            // Sort by second half first.
            vector<int> cnt(classes, 0);

            auto second_rank = [&](int i) -> int {
                return (i + k < n ? rank_[i + k] + 1 : 0);
            };

            for (int i = 0; i < n; ++i)
                cnt[second_rank(i)]++;

            for (int i = 1; i < classes; ++i)
                cnt[i] += cnt[i - 1];

            for (int i = n - 1; i >= 0; --i) {
                int x = sa[i];
                sa2[--cnt[second_rank(x)]] = x;
            }

            // Sort by first half.
            fill(cnt.begin(), cnt.end(), 0);

            auto first_rank = [&](int i) -> int {
                return rank_[i] + 1;
            };

            for (int i = 0; i < n; ++i)
                cnt[first_rank(i)]++;

            for (int i = 1; i < classes; ++i)
                cnt[i] += cnt[i - 1];

            for (int i = n - 1; i >= 0; --i) {
                int x = sa2[i];
                sa[--cnt[first_rank(x)]] = x;
            }

            // Recalculate classes.
            tmp[sa[0]] = 0;
            int new_classes = 1;

            for (int i = 1; i < n; ++i) {
                int a = sa[i - 1];
                int b = sa[i];

                pair<int, int> pa = {
                    rank_[a],
                    a + k < n ? rank_[a + k] : -1
                };

                pair<int, int> pb = {
                    rank_[b],
                    b + k < n ? rank_[b + k] : -1
                };

                if (pa != pb)
                    ++new_classes;

                tmp[b] = new_classes - 1;
            }

            rank_.swap(tmp);

            if (new_classes == n)
                break;

            if (k > n)
                break;
        }
    }

    void build_lcp() {
        lcp.assign(n, 0);

        vector<int> pos(n);

        for (int i = 0; i < n; ++i)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; ++i) {
            int r = pos[i];

            if (r == 0)
                continue;

            int j = sa[r - 1];

            while (
                i + h < n &&
                j + h < n &&
                s[i + h] == s[j + h]
            ) {
                ++h;
            }

            lcp[r] = h;

            if (h > 0)
                --h;
        }
    }
};


/*
    ============================================================
    Main
    ============================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    /*
        --------------------------------------------------------
        1. Prefix balance
        --------------------------------------------------------

        pref[i] = balance de s[0 .. i-1].

        pref[0] = 0.
    */
    vector<int> pref(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        pref[i + 1] =
            pref[i] + (s[i] == '(' ? 1 : -1);
    }


    /*
        --------------------------------------------------------
        2. Para cada posición k calculamos:

           nxt[k] = primer índice j > k tal que
                    pref[j] < pref[k].

        Si estamos empezando un substring en l, entonces su
        balance inicial es pref[l-1].

        Por lo tanto podemos llegar hasta nxt[l-1]-1.
        --------------------------------------------------------
    */

    vector<int> nxt(n + 1, n + 1);

    vector<int> st;
    st.reserve(n + 1);

    for (int i = n; i >= 0; --i) {
        while (!st.empty() && pref[st.back()] >= pref[i])
            st.pop_back();

        if (!st.empty())
            nxt[i] = st.back();

        st.push_back(i);
    }


    /*
        --------------------------------------------------------
        3. Agrupamos las posiciones según su prefix balance.

        positions[b] contiene todos los índices j tales que
        pref[j] == b.

        Después podemos hacer:

          cantidad de j en [L,R] con pref[j] == b

        mediante dos binary_search.
        --------------------------------------------------------
    */

    const int OFFSET = n + 1;

    vector<vector<int>> positions(2 * n + 3);

    for (int i = 0; i <= n; ++i) {
        positions[pref[i] + OFFSET].push_back(i);
    }


    /*
        --------------------------------------------------------
        4. Suffix Array + LCP
        --------------------------------------------------------
    */

    SuffixArray SA(s);


    /*
        --------------------------------------------------------
        5. Procesamos los sufijos en orden lexicográfico.

        Supongamos:

            l = SA.sa[k]

        El LCP con el sufijo anterior es:

            SA.lcp[k]

        Todos los prefijos de longitud <= LCP ya fueron
        contados antes.

        Por eso solo queremos substrings correctos con:

            longitud > LCP

        Si el substring comienza en l:

            endpoint >= l + LCP

        --------------------------------------------------------
    */

    ll answer = 0;

    for (int k = 0; k < n; ++k) {
        int l = SA.sa[k];

        int common = SA.lcp[k];

        /*
            El substring comienza en l.

            Su balance inicial es:
                pref[l]

            porque pref[x] representa s[0..x-1].

            Para el substring s[l..r], el balance debe volver
            a pref[l].

            Además no puede caer por debajo de pref[l].
        */

        int initial_balance = pref[l];

        /*
            nxt[l] = primera posición donde el balance cae
            estrictamente por debajo de pref[l].

            Por tanto el último endpoint posible es:

                nxt[l] - 1

            Si nunca cae, es n.
        */
        int R;

        if (nxt[l] == n + 1)
            R = n;
        else
            R = nxt[l] - 1;

        /*
            Los prefijos que ya aparecieron por un sufijo
            anterior tienen longitud <= common.

            Entonces el endpoint debe satisfacer:

                r - l + 1 > common

            =>

                r >= l + common
        */
        int L = l + common;

        if (L > R)
            continue;

        /*
            Queremos contar posiciones r en [L,R] tales que:

                pref[r] == pref[l]

            Cada una corresponde a una secuencia correcta.
        */

        auto &v = positions[initial_balance + OFFSET];

        auto it1 = lower_bound(v.begin(), v.end(), L);
        auto it2 = upper_bound(v.begin(), v.end(), R);

        answer += (it2 - it1);
    }

    cout << answer << '\n';

    return 0;
}
