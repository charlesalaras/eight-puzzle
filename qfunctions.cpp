#include "queue.h"
#include "board.h"
#include "node.h"
#include <utility>

Queue uniformCost(Queue& q, std::vector<Node*> expanded) {
    // No heuristics
    for(auto node: expanded) q.insert(node);
    return q;
}

Queue misplacedTile(Queue& q, std::vector<Node*> expanded) {
    // Heuristic: Number of misplaced tiles
    for(auto node: expanded) {
        // Evaluate the current node
        int currHeuristic = 0;
        int count = 1;
        for(int i = 0; i < node->state.n; i++) {
            for(int j = 0; j < node->state.n; j++) {
                if(i == node->state.n - 1 && j == node->state.n - 1) count = 0;
                if(node->state.data[i][j] != count) currHeuristic++;
                count++;
            }
        }
        node->heuristic = currHeuristic;
        q.insert(node);
    }
    // Reorganize the queue
    return q;
}

Queue manhattanDist(Queue& q, std::vector<Node*> expanded) {
    // Heuristic: Distance from correct position
    for(auto node: expanded) {
        // Evaluate the current node
        int currHeuristic = 0;
        int count = 1;
        for(int i = 0; i < node->state.n; i++) {
            for(int j = 0; j < node->state.n; j++) {
                if(i == node->state.n - 1 && j == node->state.n - 1) count = 0;
                if(node->state.data[i][j] != count) {
                    std::pair<int,int> truePos = {(count - 1) / node->state.n, (count - 1) % node->state.n};
                    currHeuristic += (abs(truePos.first - i) + abs(truePos.second - j));
                }
                count++;
            }
        }
        node->heuristic = currHeuristic;
        q.insert(node);
    }
    // Reorganize the queue
    return q;
}

Node* slideLeft(Node* parent) {
    if(parent->state.zeroTile.second == 0) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i][j - 1];
    child->state.data[i][j - 1] = 0;
    child->state.data[i][j] = temp;
    return child;
}

Node* slideRight(Node* parent) {
    if(parent->state.zeroTile.second == parent->state.n - 1) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i][j + 1];
    child->state.data[i][j + 1] = 0;
    child->state.data[i][j] = temp;
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
    return child;
}

Node* slideDown(Node* parent) {
    if(parent->state.zeroTile.first == parent->state.n - 1) return nullptr;
    Node* child = new Node(parent->state);
    unsigned int i = parent->state.zeroTile.first;
    unsigned int j = parent->state.zeroTile.second;
    int temp = parent->state.data[i + 1][j];
    child->state.data[i + 1][j] = 0;
    child->state.data[i][j] = temp;
    return child;
}
