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
	DepthFirstPathfinder(Graph* pGraph, Node* pFrom = NULL, Node* pTo = NULL);
	~DepthFirstPathfinder();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!
};

#endif