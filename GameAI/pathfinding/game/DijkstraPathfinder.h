#ifndef DIJKSTRA_PATHFINDER_H_
#define DIJKSTRA_PATHFINDER_H_

#include "GridPathfinder.h"

class DijkstraPathfinder : public GridPathfinder
{
public:
	DijkstraPathfinder(Graph* pGraph, Node* pFrom = nullptr, Node* pTo = nullptr);
	virtual ~DijkstraPathfinder();

	Path* findPath(Node* pFrom, Node* pTo);
};

#endif