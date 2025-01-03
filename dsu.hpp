

/*
 * Реализация системы непересекающихся множеств (3.3.2)
 */

#include <vector>

class DisjointSetUnion {

public:

    DisjointSetUnion(int n) : parent(n), w(n, 1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int GetRepr(int a) {
        while (parent[a] != parent[parent[a]])
            parent[a] = parent[parent[a]];

        return parent[a];
    }

    void Link(int a, int b) {
        a = GetRepr(a);
        b = GetRepr(b);

        if (w[a] < w[b]) {
            parent[a] = b;
            w[b] += w[a];
        } else {
            parent[b] = a;
            w[a] += w[b];
        }
    }

    bool SameSet(int a, int b) {
        return (GetRepr(a) == GetRepr(b));
    }

private:

    std::vector<int> parent;
    std::vector<int> w;
};
