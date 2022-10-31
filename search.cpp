#include "search.h"

Queue nodes;

// Helper function to expand nodes during search
std::vector<Node*> expand(Node* node, std::vector<std::function<Node*(Node*)>> operators) {
    nodes.expanded += 1;
    std::cout << "The best state to expand with g(n) = " << node->pathCost << " and " << "h(n) = " << node->heuristic << " is...\n";
    node->state.print();
    std::vector<Node*> expanded;
    for(auto i: operators) {
        Node* curr = i(node);
        // FIXME: Doesn't work
        if(curr != nullptr && !nodes.seen(curr)) {
            curr->pathCost = node->pathCost + 1;
            expanded.push_back(curr);
        };
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
    std::cout << q.maxSize << std:: endl;
    return q;
}
// Queueing function for A* with misplaced tile heuristic
Queue misplacedTile(Queue& q, std::vector<Node*> expanded) {
    // Heuristic: Number of misplaced tiles
    for(auto node: expanded) {
        // Evaluate the current node
        int currHeuristic = 0;
        int count = 1;
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                if(node->state.data[i][j] == 0) break;
                if(i == BOARD_DIM - 1 && j == BOARD_DIM - 1) count = 0;
                if(node->state.data[i][j] != count) currHeuristic++;
                count++;
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
        int count = 1;
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                
                
            }
        }
        node->heuristic = currHeuristic;
        q.insert(node);
    }
    return q;
}
/* PROBLEM OPERATORS */
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
