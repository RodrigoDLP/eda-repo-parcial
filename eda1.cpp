#include <bits/stdc++.h>

class MaxHeap {
public:
    MaxHeap(std::vector<int>& v): v(v) {}
private:
    std::vector<int> v;

    int parent(int i) {return (i-1)/2;}
    int left(int i) {return i*2+1;}
    int right(int i) {return i*2+2;}
    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int m = i;
        if (l < v.size() && v[l] > v[m]) m = l;
        if (r < v.size() && v[r] > v[m]) m = r;
        if (m != i) {
            std::swap(v[i], v[m]);
            heapify(m);
        }
    }
    void heapify_up(int i) {
        if (i == 0) return;
        int p = parent(i);
        if (v[p] < v[i]) {
            std::swap(v[p], v[i]);
            heapify_up(p);
        }
    }

public:
    void build_heap() {
        for (int i=v.size()/2 - 1; i>=0; --i)
            heapify(i);
    }
    void print_heap() {
        for (int i=0; i<v.size(); ++i) {
            std::cout << i << ": " << v[i] << " ";
        } std::cout << "\n";
    }
    int extract_max() {
        int maxelem = v[0];
        std::swap(v[0], v[v.size()-1]);
        v.pop_back();
        heapify(0);
        return maxelem;
    }
    void insert(int num) {
        v.push_back(num);
        heapify_up(v.size()-1);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    /*
    std::vector<int> v = {4, 14, 10, 8, 2, 9, 3};
    MaxHeap heap(v);
    heap.print_heap();
    heap.build_heap();
    heap.print_heap();
    */
    std::vector<int> v = {};
    MaxHeap heap(v);
    std::string temp;
    std::cin >> temp;
    while (true) {
        if (temp == "insert") {
            int num;
            std::cin >> num;
            heap.insert(num);
        } else if (temp == "extract") {
            std::cout << heap.extract_max() << "\n";
        } else if (temp == "end") break;
        std::cin >> temp;
    }
}


