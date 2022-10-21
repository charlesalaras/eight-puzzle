#ifndef __QUEUE_H__
#include "node.h"
#include <vector>

struct Queue {
    std::vector<Node*> data;
    std::vector<Node*> deletion;
    Queue();
    ~Queue() {
        for(auto state: deletion) delete state;
    }
    Queue(Node* initial) {
        data.push_back(initial);
    }
    Node* remove_front() {
        deletion.push_back(data[0]);
        return data[0];
    }
    bool insert(Node* node) {
        data.push_back(node);
        return true;
    }
    bool empty() { return data.empty(); }
};

#endif // __QUEUE_H__
