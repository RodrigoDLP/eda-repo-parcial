#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int INF = 1e9;
const int MAXA = 100000;


/*
    ============================================================
    Data del nodo
    ============================================================

    mn  = menor índice almacenado en este rango de valores.
    cnt = cantidad de elementos almacenados en este rango.
*/
struct Data {
    int mn;
    int cnt;

    Data(int mn = INF, int cnt = 0)
        : mn(mn), cnt(cnt) {}
};


/*
    Combinar dos nodos:

        - el mínimo índice
        - la suma de cantidades
*/
Data operator+(const Data& a, const Data& b) {
    return Data(
        min(a.mn, b.mn),
        a.cnt + b.cnt
    );
}


/*
    ============================================================
    Persistent Segment Tree
    ============================================================

    Esta es una versión muy cercana a la estructura original.

    Diferencias pequeñas:

    1. Los límites l/r no se guardan en cada nodo.
       Se pasan como parámetros.

    2. Usamos un pool de nodos para evitar millones de new.

    3. nullptr representa un árbol vacío.

    Cada versión representa un sufijo:

        root[i] = elementos a[i], a[i+1], ..., a[n-1]

    y cada elemento se guarda en la posición correspondiente a
    su valor a[i].
*/
struct PersistentSegmentTree {

    struct SegmentTreeNode {
        Data data;
        SegmentTreeNode *left, *right;

        SegmentTreeNode(
            Data data = Data(),
            SegmentTreeNode* left = nullptr,
            SegmentTreeNode* right = nullptr
        ) : data(data), left(left), right(right) {}
    };

    vector<SegmentTreeNode*> version_roots;

    /*
        Pool de nodos.

        Como cada update crea O(log MAXA) nodos, con
        n <= 5e5 tenemos alrededor de 9 millones de nodos.
    */
    vector<SegmentTreeNode> pool;

    PersistentSegmentTree(int max_updates) {
        version_roots.reserve(max_updates + 1);

        /*
            Aproximadamente:

                log2(100000) + 1 <= 18

            nodos por update.
        */
        pool.reserve((size_t)max_updates * 19 + 5);

        // Versión 0 = árbol vacío.
        version_roots.push_back(nullptr);
    }


    /*
        --------------------------------------------------------
        UPDATE
        --------------------------------------------------------

        Inserta un elemento:

            position = valor
            value    = { índice, 1 }

        Si ya había elementos con ese mismo valor, acumulamos:

            cnt += 1
            mn  = min(mn, índice)
    */
    SegmentTreeNode* update(
        SegmentTreeNode* last,
        int l,
        int r,
        int pos,
        Data value
    ) {
        Data old_data = last ? last->data : Data();

        SegmentTreeNode* curr;

        if (last) {
            curr = &pool.emplace_back(
                last->data,
                last->left,
                last->right
            );
        }
        else {
            curr = &pool.emplace_back(
                Data(),
                nullptr,
                nullptr
            );
        }

        if (l == r) {
            /*
                Acumulamos el elemento en esta posición.
            */
            curr->data = old_data + value;
            return curr;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) {
            curr->left = update(
                last ? last->left : nullptr,
                l,
                mid,
                pos,
                value
            );
        }
        else {
            curr->right = update(
                last ? last->right : nullptr,
                mid + 1,
                r,
                pos,
                value
            );
        }

        Data left_data =
            curr->left ? curr->left->data : Data();

        Data right_data =
            curr->right ? curr->right->data : Data();

        curr->data = left_data + right_data;

        return curr;
    }


    /*
        Crea una nueva versión a partir de "version".
    */
    int update(
        int version,
        int pos,
        Data value
    ) {
        SegmentTreeNode* root = update(
            version_roots[version],
            1,
            MAXA,
            pos,
            value
        );

        version_roots.push_back(root);

        return (int)version_roots.size() - 1;
    }


    /*
        --------------------------------------------------------
        QUERY
        --------------------------------------------------------

        Devuelve:

            mn = menor índice en [ql, qr]
            cnt = cantidad de elementos en [ql, qr]
        */
    Data query(
        SegmentTreeNode* root,
        int l,
        int r,
        int ql,
        int qr
    ) {
        if (!root || qr < l || r < ql)
            return Data();

        if (ql <= l && r <= qr)
            return root->data;

        int mid = (l + r) >> 1;

        Data left_data = query(
            root->left,
            l,
            mid,
            ql,
            qr
        );

        Data right_data = query(
            root->right,
            mid + 1,
            r,
            ql,
            qr
        );

        return left_data + right_data;
    }


    Data query(
        int version,
        int ql,
        int qr
    ) {
        if (ql > qr)
            return Data();

        ql = max(ql, 1);
        qr = min(qr, MAXA);

        if (ql > qr)
            return Data();

        return query(
            version_roots[version],
            1,
            MAXA,
            ql,
            qr
        );
    }
};


/*
    ============================================================
    solveIncreasing
    ============================================================

    Cuenta pares (i,j), i < j, para los cuales existe una cadena:

        i = p1 < p2 < ... < pm = j

    tal que:

        a[p1] < a[p2] < ... < a[pm]

    y cada diferencia consecutiva <= k.
*/
ll solveIncreasing(
    const vector<int>& a,
    int k
) {
    int n = (int)a.size();

    /*
        root[i+1] representará:

            a[i+1], a[i+2], ..., a[n-1]

        Es decir, exactamente los elementos que están a la
        derecha de i.
    */
    PersistentSegmentTree pst(n);

    vector<int> root(n + 1);

    /*
        root[n] = conjunto vacío.
    */
    root[n] = 0;

    vector<ll> dp(n, 0);

    ll answer = 0;

    /*
        Vamos de derecha a izquierda.
    */
    for (int i = n - 1; i >= 0; --i) {

        /*
            Buscamos:

                a[i] < a[j] <= a[i] + k

            y queremos el menor índice j.
        */
        int L = a[i] + 1;
        int R = a[i] + k;

        Data best = pst.query(
            root[i + 1],
            L,
            R
        );

        int j = best.mn;

        if (j != INF) {

            /*
                Cantidad de posiciones x > i con:

                    a[i] < a[x] <= a[j]
            */
            Data between = pst.query(
                root[i + 1],
                a[i] + 1,
                a[j]
            );

            /*
                Todos los caminos que empiezan en i:

                    - o bien terminan en alguno de esos
                      "primeros" candidatos;
                    - o continúan mediante j.
            */
            dp[i] = dp[j] + between.cnt;
        }
        else {
            dp[i] = 0;
        }

        answer += dp[i];

        /*
            Creamos la versión que además contiene a[i].
        */
        root[i] = pst.update(
            root[i + 1] == -1 ? 0 : root[i + 1],
            a[i],
            Data(i, 1)
        );
    }

    return answer;
}


/*
    ============================================================
    Main
    ============================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {

        int n, k;
        cin >> n >> k;

        vector<int> a(n);

        /*
            Contamos los pares con:

                a[l] == a[r]

            incluyendo l == r.
        */
        vector<ll> freq(MAXA + 1, 0);

        ll equal = 0;

        for (int i = 0; i < n; ++i) {
            cin >> a[i];

            /*
                Cada nueva aparición de x forma un par con
                todas las apariciones anteriores de x,
                además de (i,i).

                Si antes había f apariciones:

                    f + 1

                nuevos pares.
            */
            equal += ++freq[a[i]];
        }

        /*
            Parte estrictamente creciente.
        */
        ll increasing = solveIncreasing(a, k);

        /*
            Parte estrictamente decreciente.

            Al invertir el array, una secuencia decreciente
            en el array original se convierte en una secuencia
            creciente.
        */
        reverse(a.begin(), a.end());

        ll decreasing = solveIncreasing(a, k);

        cout << equal + increasing + decreasing << '\n';
    }

    return 0;
}
