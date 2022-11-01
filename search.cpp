#include "search.h"

Queue nodes;
extern bool DEBUG;
// Helper function to call all operators, and enqueue them if valid (non repeated / possible move)
std::vector<Node*> expand(Node* node, std::vector<std::function<Node*(Node*)>> operators) {
    nodes.expanded += 1;
    if(!DEBUG) {
        std::cout << "The best state to expand with g(n) = " << node->pathCost << " and " << "h(n) = " << node->heuristic << " is...\n";
        node->state.print();
    }
    std::vector<Node*> expanded;
    for(auto i: operators) {
        Node* curr = i(node);
        if(curr != nullptr) {
            if(!nodes.seen(curr)) {
                curr->pathCost = node->pathCost + 1;
                expanded.push_back(curr);
            }
            else {
                delete curr;
            }
        }
    }
    delete node;
    return expanded;
}
// The general search algorithm as described in lecture slides
Node* generalSearch(Problem problem, std::function<Queue(Queue&, std::vector<Node*>)>queueingFunction) {
    nodes = Queue(new Node(problem.initialState));
    while(1) {
        if(nodes.empty()) return nullptr;
        Node* node = nodes.remove_front();
        if(problem.goalTest(node->state)) return node;
        nodes = queueingFunction(nodes, expand(node, problem.operators));
    }
    return nullptr;
}
// Queueing function for uniform cost search
Queue uniformCost(Queue& q, std::vector<Node*> expanded) {
    // No heuristics
    for(auto node: expanded) q.insert(node);
    return q;
}
// Queueing function for A* with misplaced tile heuristic
Queue misplacedTile(Queue& q, std::vector<Node*> expanded) {
    // Heuristic: Number of misplaced tiles
    for(auto node: expanded) {
        // Evaluate the current node
        int currHeuristic = 0;
        int count = 0;
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                count++;
                if(node->state.data[i][j] == 0) continue;
                if(i == BOARD_DIM - 1 && j == BOARD_DIM - 1) count = 0;
                if(node->state.data[i][j] != count) currHeuristic++;
            }
        }
        node->heuristic = currHeuristic;
        q.insert(node);
    }
    return q;
}
// Queueing function for A* with Manhanttan distance heuristic
Queue manhattanDist(Queue& q, std::vector<Node*> expanded) {
    // Heuristic: Distance from correct position
    for(auto node: expanded) {
        // Evaluate the current node
        int currHeuristic = 0;
        int count = 0;
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                count++;
                if(node->state.data[i][j] == 0) continue;
                if(i == BOARD_DIM - 1 && j == BOARD_DIM - 1) count = 0;
                std::pair<int, int> truePos = {(node->state.data[i][j] - 1) / BOARD_DIM, (node->state.data[i][j] - 1) % BOARD_DIM};
                if(node->state.data[i][j] != count) {
                    int addedValue = abs(truePos.first - (int)i) + abs(truePos.second - (int)j);
                    currHeuristic += addedValue;
                }
            }
        }
        node->heuristic = currHeuristic;
        q.insert(node);
    }
    return q;
} 
// PROBLEM OPERATORS
// 1. Check if move is possible
// 2. Grab indices of movement
// 3. Perform swap
Node* slideLeft(Node* parent) {
    if(parent->state.zeroTile.second == 0) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i][j - 1];
    child->state.data[i][j - 1] = 0;
    child->state.data[i][j] = temp;
    child->state.zeroTile = {i, j - 1};
    return child;
}

Node* slideRight(Node* parent) {
    if(parent->state.zeroTile.second == BOARD_DIM - 1) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i][j + 1];
    child->state.data[i][j + 1] = 0;
    child->state.data[i][j] = temp;
    child->state.zeroTile = {i, j + 1};
    return child;
}

Node* slideUp(Node* parent) {
    if(parent->state.zeroTile.first == 0) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i - 1][j];
    child->state.data[i - 1][j] = 0;
    child->state.data[i][j] = temp;
    child->state.zeroTile = {i - 1, j};
    return child;
}

Node* slideDown(Node* parent) {
    if(parent->state.zeroTile.first == BOARD_DIM - 1) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i + 1][j];
    child->state.data[i + 1][j] = 0;
    child->state.data[i][j] = temp;
    child->state.zeroTile = {i + 1, j};
    return child;
}
