#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

#include "DepthFirstPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"

DepthFirstPathfinder::DepthFirstPathfinder(Graph* pGraph, Node* pFrom, Node* pTo)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph), pFrom, pTo)
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;

	if (mpFrom && mpTo)
	{
		findPath(mpFrom, mpTo);
	}
#endif
}

DepthFirstPathfinder::~DepthFirstPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* DepthFirstPathfinder::findPath( Node* pFrom, Node* pTo )
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	
	setNodes(pFrom, pTo);

	//allocate nodes to visit list and place starting node in it
	std::list<Node*> nodesToVisit;
	nodesToVisit.push_front( pFrom );

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back( pFrom );
#endif
	
	//create Path
	Path* pPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while( pCurrentNode != pTo && nodesToVisit.size() > 0 )
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		pPath->addNode( pCurrentNode );

		//get the Connections for the current node
		std::vector<Connection*> connections = mpGraph->getConnections( pCurrentNode->getId() );

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for( unsigned int i=0; i<connections.size(); i++ )
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if( !toNodeAdded && 
				!pPath->containsNode( pTempToNode ) && 
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode ) == nodesToVisit.end() )
			{
				nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				if( pTempToNode == pTo )
				{
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back( pTempToNode );
#endif
			}
		}
	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;

}

