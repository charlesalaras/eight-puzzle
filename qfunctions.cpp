#include "queue.h"
#include "node.h"

Queue uniformCost(Queue q, std::vector<Node*> expanded) {
    // No heuristics
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
