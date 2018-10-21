#ifndef ASTAR_PATHFINDER_H_
#define ASTAR_PATHFINDER_H_

#include "GridPathfinder.h"

class AStarPathfinder : public GridPathfinder
{
public:
	AStarPathfinder(Graph* pGraph, Node* pFrom = NULL, Node* pTo = NULL);
	virtual ~AStarPathfinder();

	Path* findPath(Node* pFrom, Node* pTo);
};

#endif