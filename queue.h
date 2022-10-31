#ifndef __QUEUE_H__
#include "board.h"
#include "node.h"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

class Compare {
    public:
    bool operator() (const Node* lhs, const Node* rhs) const {
        int left = lhs->heuristic + lhs->pathCost;
        int right = rhs->heuristic + rhs->pathCost;
        return left > right;
    }
};

struct Queue {
    std::priority_queue<Node*, std::vector<Node*>, Compare> data;
    std::unordered_set<std::string> hashMap = {};
    long int expanded = 0;
    long int maxSize = 0;
    Queue() = default;
    void clear() {
        while(!data.empty()) {
            delete data.top();
            data.pop();
        }
    }
    Queue(Node* initial) {
        data.push(initial);
    }
    Node* remove_front() {
        Node* returnData = data.top();
        data.pop();
        return returnData;
    }
    // Returns false is node hasn't been seen (inserted successfully), true otherwise.
    bool seen(Node* node) {
        return !hashMap.insert(node->state.stringify()).second;
    }
    // Inserts the node and updates max queue size if necessary.
    bool insert(Node* node) {
        data.push(node);
        maxSize = std::max(maxSize, (long int)data.size());
        return true;
    }
    bool empty() { return data.empty(); }
};

#endif // __QUEUE_H__
