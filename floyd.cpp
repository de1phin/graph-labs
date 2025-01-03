
/*
 * Поиск минимальных путей (§4)
 * Алгоритм Флойда (4.3)
 *
 * Пример (первый из табл. 4.1):
 *
 * $ g++ -o ./exe ./floyd.cpp
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
 * < a-d (11): a g d 
 * < a-e (7): a g e 
 * < a-f (8): a g e f 
 * < b-c (9): b a c 
 * < b-e (8): b f e 
 * < b-g (5): b a g 
 * < c-d (17): c a g d 
 * < c-e (13): c a g e 
 * < c-f (14): c a g e f 
 * < c-g (8): c a g 
 * < d-e (5): d f e 
 * < f-g (6): f e g
 *
 * (NOTE): Здесь есть различие с методичкой,
 * т.к. пути c->g (8) и c->a->g (6+2) эквиваленты.
 *
 */

#include <iostream>
#include "adj.hpp"

#define INF 1000000007
typedef std::vector<std::vector<long> > Matrix;

void Floyd(Matrix &C) {
    int n = C.size();
    for (int src = 0; src < n; src++) {
        for (int dst = 0; dst < n; dst++) {
            for (int via = 0; via < n; via++) {
                C[src][dst] = std::min(C[src][dst], C[src][via] + C[via][dst]);
            }
        }
    }
}

void FillMinimalPath(std::vector<int> &path, Matrix &C, Matrix &W, int src, int dst) {
    path.clear();

    int v = src;
    while (C[v][dst] > 0) {
        path.push_back(v);
        for (int i = 0; i < C.size(); i++) {
            if (i == v) continue;
            if (C[v][dst] == W[v][i] + C[i][dst]) {
                v = i;
                break;
            }
        }
    }
    path.push_back(v);
}

int main() {

    int n, m;
    std::cin >> n >> m;

    Matrix C(n, std::vector<long>(n, INF));
    Matrix W(n, std::vector<long>(n, INF));
    for (int i = 0; i < n; i++)
        C[i][i] = 0;

    for (int i = 0; i < m; i++) {
        char u, v; long w;
        std::cin >> u >> v >> w;
        int tail = int(u - 'a'), head = int(v - 'a');
        if (C[tail][head] > w) {
            C[tail][head] = w;
            C[head][tail] = w;
            W[tail][head] = w;
            W[head][tail] = w;
        }
    }

    Floyd(C);

    std::vector<int> path;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            FillMinimalPath(path, C, W, i, j);
            // skip adjacent
            if (path.size() == 2)
                continue;
            std::cout << char(i + 'a') << "-" << char(j + 'a') << " "
                << "(" << C[i][j] << "): ";
            for (auto &x : path)
                std::cout << char(x + 'a') << " ";
            std::cout << std::endl;
        }
    }

}
