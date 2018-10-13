#include <PerformanceTracker.h>

#include "DijkstraPathfinder.h"
#include "Path.h"
#include "GridGraph.h"
#include "Game.h"

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph) :
	GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif
}

DijkstraPathfinder::~DijkstraPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	//Do all the path stuff here!

	return nullptr;
}