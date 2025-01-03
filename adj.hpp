
/*
 * Реализация списка смежности
 * на массивах. (п. 2.2.1 методички)
 */

#define LIST_END_MARKER -1

struct Edge {
    int tail;
    int head;
    int weight;

    friend bool operator< (const Edge &lhs, const Edge &rhs) { return lhs.weight < rhs.weight; }
};

class AdjMatrix {

public:

    AdjMatrix(int n, int m) {
        count = 0;
        head = new int[n];
        next = new int[m * 2];
        adj = new Edge[m * 2];
        for (int i = 0; i < n; i++) {
            head[i] = LIST_END_MARKER;
        }
    };

    ~AdjMatrix() {
        delete head;
        delete next;
        delete adj;
    }

    void AddDirectArc(Edge edge) {
        count++;
        adj[count - 1] = edge;
        next[count - 1] = head[edge.tail];
        head[edge.tail] = count - 1;
    }

    void AddDirectArc(int tail, int head, int weight=0) {
        Edge edge = {tail, head, weight};
        AddDirectArc(edge);
    }

    inline void AddIndirectArc(int tail, int head, int weight=0) {
        AddDirectArc(tail, head, weight);
        AddDirectArc(head, tail, weight);
    }

    inline void AddIndirectArc(Edge edge) {
        AddDirectArc(edge);
        std::swap(edge.tail, edge.head);
        AddDirectArc(edge);
    }


    struct Iterator {
        Iterator(AdjMatrix *m, int p) : parent(m), pos(p) {}

        Edge& operator*() const { return parent->adj[pos]; }
        Edge* operator->() { return &parent->adj[pos]; }
        Iterator& operator++() { pos = parent->next[pos]; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator &b) { return a.pos == b.pos; }
        friend bool operator!= (const Iterator& a, const Iterator &b) { return a.pos != b.pos; }

        AdjMatrix *parent;
        int pos;
    };

    struct AdjList { 
        Iterator begin() { return Iterator(parent, parent->head[u]); }
        Iterator end() { return Iterator(parent, LIST_END_MARKER); }
        AdjList(AdjMatrix *m, int v) : parent(m), u(v) {}
        AdjMatrix *parent;
        int u;
    };

    AdjList GetAdjacent(int u) {
        return AdjList(this, u);
    }

//private:
    int count;
    int *head;
    int *next;
    Edge *adj;
};


