#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int T;
    fin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        fin >> N;

        vector<long long> A(N + 1);
        for (int i = 1; i <= N; i++) fin >> A[i];

        vector<Edge> edges;
        edges.reserve(2 * N);

        for (int i = 1; i <= N; i++) {
            edges.push_back({0, i, A[i]});
        }

        for (int i = 1; i < N; i++) {
            long long diff = llabs(A[i + 1] - A[i]);
            edges.push_back({i, i + 1, diff});
        }

        sort(edges.begin(), edges.end());

        DSU dsu(N + 1);
        long long maxEdge = 0;
        int components = N + 1;

        for (const auto &e : edges) {
            if (dsu.unite(e.u, e.v)) {
                if (e.w > maxEdge) maxEdge = e.w;
                components--;
                if (components == 1) break;
            }
        }

        fout << "Case #" << t << ": " << maxEdge << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
