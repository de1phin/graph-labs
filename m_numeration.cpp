
/*
 * M-нумерация графа (2.3.3 методички)
 * 
 * Пример (последний из табл. 2.1):
 *
 * $ g++ -o ./exe ./m_numeration.cpp
 * $ ./exe                          
 * > 5 6
 * > a b
 * > a c
 * > b d
 * > c b
 * > c e
 * > e d
 * < 1 5 2 4 3
 *
 */

#include <iostream>
#include <vector>
#include "adj.hpp"

enum Color {
    WHITE,
    GRAY,
    BLACK
};

void dfs(int u, AdjMatrix &adj, std::vector<Color> &color, 
        std::vector<int> &m_number, int &current_number) {

    color[u] = GRAY;
    m_number[u] = current_number;
    current_number++;

    for (auto &a : adj.GetAdjacent(u)) {
        if (color[a.head] != WHITE)
            continue;
        dfs(a.head, adj, color, m_number, current_number);
    }

    color[u] = BLACK;
}

int main() {

    int n, m;

    std::cin >> n >> m;

    AdjMatrix adj(n, m);

    for (int i = 0; i < m; i++) {
        char u, v;
        std::cin >> u >> v;
        adj.AddDirectArc(int(u - 'a'), int(v - 'a'));
    }

    int current_number = 1;
    std::vector<Color> color(n, WHITE);
    std::vector<int> m_number(n, 0);

    for (int i = 0; i < n; i++) {
        if (color[i] == WHITE)
            dfs(i, adj, color, m_number, current_number);
    }

    for (auto &x : m_number) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

}
