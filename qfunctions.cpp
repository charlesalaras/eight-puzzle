#include "queue.h"
#include "board.h"
#include "node.h"

Queue uniformCost(Queue q, std::vector<Node*> expanded) {
    // No heuristics
    for(unsigned int i = 0; i < expanded.size(); i++) {
        q.insert(expanded[i]);
    }
    return {};
}

Queue misplacedTile(Queue q, std::vector<Node*> expanded) {
    // Heuristic: Number of misplaced tiles
    return {};
}

Queue manhattanDist(Queue q, std::vector<Node*> expanded) {
    // Heuristic: Distance from correct position
    return {};
}

Node* slideLeft(Node* parent) {
    if(parent->state.zeroTile.second == 0) return nullptr;
    return nullptr;
}

Node* slideRight(Node* parent) {
    if(parent->state.zeroTile.second == parent->state.n - 1) return nullptr;
    return nullptr;
}

Node* slideUp(Node* parent) {
    if(parent->state.zeroTile.first == 0) return nullptr;
    return nullptr;
}

Node* slideDown(Node* parent) {
    if(parent->state.zeroTile.first == parent->state.n - 1) return nullptr;
    return nullptr;
}
