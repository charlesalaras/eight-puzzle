#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <utility>
#include <functional>

#include "node.h"
#include "queue.h"
#include "board.h"
#include "problem.h"

std::vector<Node*> expand(Node*, std::vector<std::function<Node*(Node*)>>);

Node* generalSearch(Problem, std::function<Queue(Queue&, std::vector<Node*>)>);

Queue uniformCost(Queue&, std::vector<Node*>);

Queue misplacedTile(Queue&, std::vector<Node*>);

Queue manhattanDist(Queue&, std::vector<Node*>);

#endif // __SEARCH_H__
