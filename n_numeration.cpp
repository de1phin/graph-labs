
/*
 * N-нумерация графа (2.3 методички)
 * 
 * Пример (последний из табл. 2.2):
 *
 * $ g++ -o ./exe ./n_numeration.cpp
 * $ ./exe                          
 * > 5 6
 * > a b
 * > a c
 * > b d
 * > c b
 * > c e
 * > e d
 * < 1 3 2 5 4
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
        std::vector<int> &n_number, int &current_number) {

    color[u] = GRAY;

    for (auto &a : adj.GetAdjacent(u)) {
        if (color[a.head] != WHITE)
            continue;
        dfs(a.head, adj, color, n_number, current_number);
    }

    color[u] = BLACK;
    n_number[u] = current_number;
    current_number--;
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

    int current_number = n;
    std::vector<Color> color(n, WHITE);
    std::vector<int> n_number(n, 0);

    for (int i = 0; i < n; i++) {
        if (color[i] == WHITE)
            dfs(i, adj, color, n_number, current_number);
    }

    for (auto &x : n_number) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

}
