
/*
 * Реализация очереди с приоритетом (5.3)
 */

#include <vector>

template<typename Key, typename Priority>
class MinHeap {

public:

    typedef std::pair<Key, Priority> Element;

    MinHeap() : count(0) {}
    MinHeap(int size) : count(0) {
        heap.reserve(size);
    }

    void Insert(Element element) {
        if (count == heap.size())
            heap.push_back(element);
        else
            heap[count] = element;
        count++;

        heapifyUp(count - 1);
    }

    inline void Insert(Key key, Priority priority) {
        Insert(std::make_pair(key, priority));
    }

    bool Empty() {
        return (count == 0);
    }

    Element GetMin() {
        return heap[0];
    }

    Element PopMin() {
        Element ret = heap[0];
        heap[0] = heap[count - 1];
        count--;
        if (count > 0)
            heapifyDown(0);
        return ret;
    }

private:

    void heapifyUp(int idx) {
        while (idx > 0 && heap[idx].second < heap[(idx - 1) / 2].second) {
            std::swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void heapifyDown(int idx) {
        while (idx < count) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int minIdx = idx;
            if (left < count && heap[left].second < heap[minIdx].second)
                minIdx = left;
            if (right < count && heap[right].second < heap[minIdx].second)
                minIdx = right;
            if (minIdx == idx)
                break;
            std::swap(heap[idx], heap[minIdx]);
            idx = minIdx;
        }
    }

    int count;
    std::vector<Element> heap;

};
