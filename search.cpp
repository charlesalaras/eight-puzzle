#include <functional>
#include <vector>
#include "node.h"
#include "queue.h"
#include "problem.h"

Node* expand(Node* node, std::vector<std::function<void()>> operators) {
    return nullptr;
}

Node* generalSearch(Problem problem, std::function<Queue(Queue, Node*)>queueingFunction) {
    Queue nodes = Queue(new Node(problem.initialState));
    while(1) {
        if(nodes.empty()) return nullptr;
        Node* node = nodes.remove_front();
        if(problem.goalTest(node->state)) return node;
        nodes = queueingFunction(nodes, expand(node, problem.operators));
    }
    return nullptr;
}
