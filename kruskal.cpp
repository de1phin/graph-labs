
/*
 * Поиск минимального остовного дерева (§3)
 * Алгоритм Краскала (3.2)
 *
 * Пример (первый из табл. 3-2):
 *
 * $ g++ -o ./exe ./kruskal.cpp
 * $ ./exe                     
 * > 7 10
 * > a b 3
 * > a c 6
 * > a g 2
 * > b d 10
 * > b f 7
 * > c g 8
 * > d f 4
 * > d g 9
 * > e f 1
 * > e g 5
 * < e f
 * < a g
 * < a b
 * < d f
 * < e g
 * < a c
 * < Cost = 21
 *
 */

#include <iostream>
#include <vector>
#include "adj.hpp"
#include "dsu.hpp"

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        char tail, head;
        std::cin >> tail >> head >> edges[i].weight;
        edges[i].tail = int(tail - 'a');
        edges[i].head = int(head - 'a');
    }

    int cost = 0;
    DisjointSetUnion dsu(n);

    std::sort(edges.begin(), edges.end());

    for (auto &edge : edges) {
        if (dsu.SameSet(edge.tail, edge.head))
            continue;
        cost += edge.weight;
        dsu.Link(edge.tail, edge.head);

        std::cout << char('a' + edge.tail) << " " << char('a' + edge.head) << std::endl;
    }

    std::cout << "Cost = " << cost << std::endl;
}