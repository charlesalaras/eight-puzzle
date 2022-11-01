#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <utility>
#include <functional>

#include "node.h"
#include "queue.h"
#include "board.h"
#include "problem.h"

// Applies every operator to the parent node, attempting to create children
// Places all valid / legal nodes from the operators into a list, as long as it wasn't seen before
// Finally returns the list to be concatenated into the queue after being evaluated for its heuristic.
std::vector<Node*> expand(Node*, std::vector<std::function<Node*(Node*)>>);
// The general search algorithm presented in lecture
Node* generalSearch(Problem, std::function<Queue(Queue&, std::vector<Node*>)>);
// The queueing function for uniform cost search. The function simply enqueues the nodes as they come.
Queue uniformCost(Queue&, std::vector<Node*>);
// The queueing function for misplaced tile heuristic A*. The function looks at every tile (except for the blank)
// and checks if its in the correct position based on what should be there. If not, we add 1 to the heuristic.
// The priority queue will take care of sorting for us.
Queue misplacedTile(Queue&, std::vector<Node*>);
// The queueing function for Manhattan distance A*. The function looks at every tile (except for the blank)
// and checks where its true position should be (modulo / division operations). Based on this, we calculate
// distance with the x and y coordinates, and add that to the heuristic.
// The priority queue will take care of sorting for us.
Queue manhattanDist(Queue&, std::vector<Node*>);

#endif // __SEARCH_H__
