#ifndef __QUEUE_H__
#include "node.h"
#include <vector>

class Queue {
    public:
        Queue();
        ~Queue();
        Queue(Node* initial);
        std::vector<Node*> data;
        Node* remove_front();
        bool empty() { return data.empty(); }
};

#endif // __QUEUE_H__
