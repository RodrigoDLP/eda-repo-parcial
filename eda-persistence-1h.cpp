#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



template<typename data_type>
struct PersistentSegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentSegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentSegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data = value;
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = curr -> left -> data + curr -> right -> data;
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }
    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};

template<typename data_type>
struct PersistentFrequencySegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentFrequencySegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentFrequencySegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data += value; //cambio está aquí
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = curr -> left -> data + curr -> right -> data;
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }
    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};


int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<int> v(n); for (int i=0; i<n; ++i) cin >> v[i];

    //compresión de coordenadas para que el tamaño del árbol posteriormente sea n y no 10^9. O(n)
    vector<int> compressor(v.begin(), v.end());
    sort(compressor.begin(), compressor.end());
    compressor.erase(unique(compressor.begin(), compressor.end()), compressor.end());
    for (int i=0; i<n; ++i) v[i] = lower_bound(compressor.begin(), compressor.end(), v[i]) - compressor.begin();


    PersistentFrequencySegmentTree<int> tree(compressor.size()); //N tamaño del árbol, tras comprimir N = n, sino N = tam máx a_i = 10^9
    //insertar elementos por rangos del array original: [1, 1], [1, 2], [1, 3]. cada árbol tiene valor: #elementos con ese valor
    for (int i=0; i<n; ++i) tree.update(i, v[i], 1); //update pos v[i] ya que ese es el número, le suma 1. O(NlgN)
    int q, temp1, temp2, temp3; cin >> q;
    int lastans = 0;
    for (int i=0; i<q; ++i) {
        cin >> temp1 >> temp2 >> temp3;
        temp1 = temp1 ^ lastans;
        temp2 = temp2 ^ lastans;
        temp3 = temp3 ^ lastans;
        if (temp1 > n || temp2 < 1) lastans = 0;
        else {
            if (temp1 < 1) temp1 = 1;
            if (temp2 > n) temp2 = n;

            //obtener la posición del elemento k: su índice comprimido. recordar que compressor tiene los elementos originales, solo en v se usa lowerbound
            //en este caso usamos upperbound porque queremos el índice del primer elemento mayor a k para procesar [primero después de k, final]
            int begin = upper_bound(compressor.begin(), compressor.end(), temp3) - compressor.begin();
            //[primero postk, final] = cantidad de elementos mayores que k con los elementos de la versión establecida ([1, versión]). se hace #[1, r] - #[1, l-1]
            lastans = tree.query(temp2, begin, (int)compressor.size()-1) - tree.query(temp1-1, begin, (int)compressor.size()-1);
        }
        cout << lastans << "\n";
    } //O(klgN)
}
