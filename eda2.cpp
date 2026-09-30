#include <bits/stdc++.h>

class MinHeapPair {
public:
    MinHeapPair(std::vector<std::pair<int, int>>& v): v(v) {}
    ~MinHeapPair() {
        delete_all();
        v.resize(0);
    }
private:
    std::vector<std::pair<int, int>> v;
    std::unordered_map<int, int> vertexindexes;
    int parent(int i) {return (i-1)/2;}
    int left(int i) {return i*2+1;}
    int right(int i) {return i*2+2;}
    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int m = i;
        if (l < v.size() && v[l].second < v[m].second) m = l;
        if (r < v.size() && v[r].second < v[m].second) m = r;
        if (m != i) {
            int temp = vertexindexes[v[i].first];
            vertexindexes[v[i].first] = vertexindexes[v[m].first];
            vertexindexes[v[m].first] = temp;
            std::swap(v[i], v[m]);
            heapify(m);
        }
    }
    void heapify_up(int i) {
        if (i == 0) return;
        int p = parent(i);
        if (v[p].second > v[i].second) {
            int temp = vertexindexes[v[i].first];
            vertexindexes[v[i].first] = vertexindexes[v[p].first];
            vertexindexes[v[p].first] = temp;
            std::swap(v[p], v[i]);
            heapify_up(p);
        }
    }

public:
    void build_heap() {
        for (int i=v.size()/2 - 1; i>=0; --i)
            heapify(i);
    }
    void delete_all() {v.clear(); vertexindexes.clear();}
    void print_heap() {
        std::cout << "Printing heap\n";
        for (int i=0; i<v.size(); ++i) {
            std::cout << i << ": " << v[i].first << ", w=" << v[i].second << " | ";
        } std::cout << "\n";
    }
    std::pair<int, int> extract_min() {
        std::pair<int, int> minelem = v[0];
        int temp = vertexindexes[v[0].first];
        vertexindexes[v[0].first] = -1;
        vertexindexes[v[v.size()-1].first] = temp;
        std::swap(v[0], v[v.size()-1]);
        v.pop_back();
        heapify(0);
        //std::cout << "minelem " << minelem.first << "extracted\n";
        return minelem;
    }
    void insert(std::pair<int, int> num) {
        //std::cout << "inserting " << num.first << " with weight " << num.second << "\n";
        v.push_back(num);
        vertexindexes[num.first] = v.size()-1;
        heapify_up(v.size()-1);
        //print_heap();
    }
    bool empty() {return v.empty();}
    void decrease_key(int vertex, int newval) {
        //std::cout << "trying decrease_key on vertex " << vertex << "\n";
        //if (vertexindexes[vertex] > v.size() || vertexindexes[vertex] == -1) {
        //    std::cout << "decrease_key on vertex " << vertex << " unsuccessful\n";
        //    return;
        //}

            //throw std::runtime_error("DECKEY OUT OF RANGE");
        //std::cout << "decreasing " << vertex << " on foundindex=" << vertexindexes[vertex] << " from " << v[vertexindexes[vertex]].second << " to weight " << newval << "\n";
        v[vertexindexes[vertex]].second = newval;
        //heapify up solamente porque el elemento se va a reducir con newval
        heapify_up(vertexindexes[vertex]);
        //print_heap();
    }
};


    //algoritmo adaptado de (Cormen et al., 2022)
    void dijkstra(int n, int start, int finish,
        std::unordered_map<int, std::vector<std::pair<int, int>>>& edgev) {
        //std::cout << "realrealstart was successful\n";
        std::vector<std::pair<int, int>> heapvector;
        MinHeapPair heap(heapvector);
        //std::cout << "realstart was successful\n";
        std::vector<int> dist, parent;
        //std::set<int> visited;
        for (int i=0; i<n; ++i) {dist.push_back(INT_MAX); parent.push_back(0);}
        dist[start-1] = 0;

        //std::cout << "start was successful\n";

        for (int i=1; i<=n; ++i) heap.insert(std::make_pair(i, INT_MAX));
        heap.decrease_key(start, 0);
        while (!heap.empty()) {
            const auto& u = heap.extract_min();
            int currv = u.first;
            if (u.second > dist[currv-1]) continue;
            //visited.insert(u.first);
            for (const auto& edge: edgev[currv]) {
                int currv2 = edge.first;
                if (dist[currv2-1] > dist[currv-1]+edge.second) {
                    //std::cout << "edge (" << currv << ", " << currv2 << ") found useful\n";
                    dist[currv2-1] = dist[currv-1]+edge.second;
                    parent[currv2-1] = currv;
                    heap.decrease_key(currv2, dist[currv2-1]);
                }
            }
            if (currv == finish) break;
            //heap.print_heap();
        }
        int cv = finish;
        if (dist[cv-1] == INT_MAX || parent[cv-1] == 0) {
            std::cout << -1 << "\n";
            return;
        }
        /*std::vector<int> output;
        output.push_back(cv);
        while (cv != start) {
            cv = parent[cv-1];
            output.push_back(cv);
        }
        for (int i=output.size()-1; i>=0; --i) std::cout << output[i] << "\n";
        */

        std::string output = std::to_string(cv);
        int outputsize = 0;
        long long outputlength = 0;
        while (cv != start) {
            output = " " + output;
            output = std::to_string(parent[cv-1]) + output;
            outputlength = di
            cv = parent[cv-1];
            outputsize++;
        }
        std::cout << output << "\n";


        //std::cout << "DISTANCES\n";
        //for (int i=1; i<=dist.size(); ++i) std::cout << i << ": " << dist[i-1] << "\n";
    }

int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int n, m;
        std::cin >> n; std::cin >> m;
        std::unordered_map<int, std::vector<std::pair<int, int>>> edgev;
        for (int i=0; i<m; ++i) {
            int a1, a2, a3;
            std::cin >> a1;
            std::cin >> a2;
            std::cin >> a3;
            edgev[a1].push_back(std::make_pair(a2, a3));
            edgev[a2].push_back(std::make_pair(a1, a3));
        }
        //std::cout << "good\n";
        dijkstra(n, 1, n, edgev);
        return 0;
    }



