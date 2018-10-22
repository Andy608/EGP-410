#ifndef DEPTH_FIRST_PATHFINDER_H_
#define DEPTH_FIRST_PATHFINDER_H_

#include "GridPathfinder.h"
#include <vector>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DepthFirstPathfinder : public GridPathfinder
{
public:
	DepthFirstPathfinder(Graph* pGraph, Node* pFrom = nullptr, Node* pTo = nullptr);
	~DepthFirstPathfinder();

	Path* findPath(Node* pFrom, Node* pTo);
};

#endif