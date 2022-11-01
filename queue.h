#ifndef __QUEUE_H__
#include "board.h"
#include "node.h"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

// Contains the () operator which acts as a custom comparator function for the Node class
// This is crucial for the heap properties of our priority queue.
// It explicitly defines how to break ties and calculate the next chosen node.
class Compare {
    public:
    bool operator() (const Node* lhs, const Node* rhs) const {
        int left = lhs->heuristic + lhs->pathCost;
        int right = rhs->heuristic + rhs->pathCost;
        // If same, we should be choosing one with a lower depth
        if(left == right) {
            return lhs->pathCost > rhs->pathCost;
        }
	return left > right;
    }
};

struct Queue {
    std::priority_queue<Node*, std::vector<Node*>, Compare> data;
    // Stores repeated states
    std::unordered_set<std::string> hashMap = {};
    long int expanded = 0;
    // Stores maximum number of nodes in queue
    long int maxSize = 0;
    Queue() = default;
    // Called at end of search to delete remaining leaking memory
    void clear() {
        while(!data.empty()) {
            delete data.top();
            data.pop();
        }
    }
    Queue(Node* initial) {
        data.push(initial);
    }
    // Pops the front node (lowest f(n)), and returns it.
    Node* remove_front() {
        Node* returnData = data.top();
        data.pop();
        return returnData;
    }
    // Returns false if node hasn't been seen (inserted successfully), true otherwise.
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
