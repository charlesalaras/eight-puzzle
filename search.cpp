#include <functional>
#include <vector>
#include "node.h"
#include "queue.h"
#include "board.h"
#include "problem.h"

std::vector<Node*> expand(Node* node, std::vector<std::function<Node*(Board)>> operators) {
    std::vector<Node*> expanded;
    for(auto i: operators) {
        Node* curr = i(node->state);
        if(curr != nullptr) expanded.push_back(curr);
    }
    return expanded;
}

Node* generalSearch(Problem problem, std::function<Queue(Queue, std::vector<Node*>)>queueingFunction) {
    Queue nodes = Queue(new Node(problem.initialState));
    while(1) {
        if(nodes.empty()) return nullptr;
        Node* node = nodes.remove_front();
        if(problem.goalTest(node->state)) return node;
        nodes = queueingFunction(nodes, expand(node, problem.operators));
    }
    return nullptr;
}
