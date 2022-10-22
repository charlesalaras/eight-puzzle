#ifndef __QUEUE_H__
#include "node.h"
#include <vector>
#include <queue>

class Compare {
    public:
    bool operator() (const Node* lhs, const Node* rhs) const {
        int left = lhs->heuristic + lhs->pathCost;
        int right = rhs->heuristic + rhs->pathCost;
        return left < right;
    }
};

struct Queue {
    std::priority_queue<Node*, std::vector<Node*>, Compare> data;
    std::vector<Node*> deletion;
    Queue();
    ~Queue() {
        for(auto state: deletion) delete state;
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
        deletion.push_back(returnData);
        data.pop();
        return returnData;
    }
    bool insert(Node* node) {
        data.push(node);
        return true;
    }
    bool empty() { return data.empty(); }
};

#endif // __QUEUE_H__
