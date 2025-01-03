
/*
 * Кратчайшие пути от заданной вершины (§5)
 * Алгоритм Дейкстры
 *
 * Пример (последний из табл. 5-1):
 *
 * $ g++ -o ./exe ./dijkstra.cpp
 * $ ./exe
 * > 7 10 e
 * > a b 8
 * > a c 6
 * > a g 5
 * > b d 10
 * > b f 9
 * > c g 7
 * > d f 2
 * > d g 4
 * > e f 1
 * > e g 3
 * < e-a(8) : e g a 
 * < e-b(10) : e f b 
 * < e-c(10) : e g c 
 * < e-d(3) : e f d 
 * < e-f(1) : e f 
 * < e-g(3) : e g
 *
 */

#include <tuple>
#include <iostream>
#include <algorithm>
#include "adj.hpp"
#include "heap.hpp"

#define INF 1000000007

enum Color {
    WHITE,
    GRAY,
    BLACK
};

void Relax(int u, Edge e, std::vector<long> &D, 
           std::vector<Color> &colors, MinHeap<int, int> &heap) {
    int v = e.head, w = e.weight;
    if (D[v] <= D[u] + w)
        return;

    D[v] = D[u] + w;

    if (colors[v] != WHITE)
        return;

    heap.Insert(v, D[v]);
    colors[v] = GRAY;
}

int main() {

    int n, m;
    char c;
    std::cin >> n >> m >> c;

    int start = int(c - 'a');

    AdjMatrix adj(n, m);
    for (int i = 0; i < m; i++) {
        char u, v; int w;
        std::cin >> u >> v >> w;
        adj.AddIndirectArc(int(u - 'a'), int(v - 'a'), w);
    }

    MinHeap<int, int> heap;

    std::vector<long> D(n, INF);
    D[start] = 0;

    std::vector<Color> colors(n, WHITE);

    colors[start] = GRAY;
    heap.Insert(start, 0);

    while (!heap.Empty()) {
        int u, d;
        std::tie(u, d) = heap.PopMin();
        colors[u] = BLACK;

        for (auto &e : adj.GetAdjacent(u)) {
            Relax(u, e, D, colors, heap);
        }
    }

    std::vector<int> previous(n, 0);
    for (int i = 0; i < n; i++) {
        for (auto &e : adj.GetAdjacent(i)) {
            if (D[e.head] == D[e.tail] + e.weight)
                previous[e.head] = e.tail;
        }
    }

    std::vector<int> path;
    path.reserve(n);

    for (int i = 0; i < n; i++) {
        if (i == start) continue;

        path.clear();
        int v = i;
        path.push_back(v);
        while (v != start) {
            v = previous[v];
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());

        std::cout << char(start + 'a') << "-" << char(i + 'a')
            << "(" << D[i] << ") : ";
        for (auto &x : path)
            std::cout << char(x + 'a') << " ";
        std::cout << std::endl;
    }

}
