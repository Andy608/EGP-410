#ifndef PATHFINDING_DEBUG_CONTENT_H_
#define PATHFINDING_DEBUG_CONTENT_H_

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent( GridPathfinder* pPathfinder );
	~PathfindingDebugContent(){};

	std::string getDebugString();

private:
	GridPathfinder* mpPathfinder;
};

#endif