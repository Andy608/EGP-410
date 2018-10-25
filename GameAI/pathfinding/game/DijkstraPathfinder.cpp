#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

#include "DijkstraPathfinder.h"
#include "Path.h"
#include "GridGraph.h"
#include "Game.h"

#include "PathfindingList.h"

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph, Node* pFrom, Node* pTo) :
	GridPathfinder(dynamic_cast<GridGraph*>(pGraph), pFrom, pTo)
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;

	if (mpFrom && mpTo)
	{
		findPath(mpFrom, mpTo);
	}
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

	setNodes(pFrom, pTo);

	NodeRecord startRecord = NodeRecord(pFrom, nullptr, 0.0f);

	PathfindingList openList;
	openList.addBasedOnCost(startRecord);

	PathfindingList closedList;

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	Path* pPath = new Path();
	NodeRecord current;

	while (openList.size() > 0)
	{
		openList.getSmallestElement(current);

		if (current.node == pTo)
		{
			break;
		}
		
		std::vector<Connection*> connections = mpGraph->getConnections(current.node->getId());
		
		for (Connection* currentConnection : connections)
		{
			Node* endNode = currentConnection->getToNode();
			float endNodeCost = current.costSoFar + currentConnection->getCost();
			NodeRecord endNodeRecord;

			if (closedList.contains(endNode))
			{
				continue;
			}
			else if (openList.contains(endNode))
			{
				openList.find(endNode, endNodeRecord);

				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					continue;
				}
			}
			else
			{
				endNodeRecord = NodeRecord();
				endNodeRecord.node = endNode;
			}

			endNodeRecord.connection = currentConnection;
			endNodeRecord.costSoFar = endNodeCost;

			if (!openList.contains(endNode))
			{
				openList.addBasedOnCost(endNodeRecord);
			}

#ifdef VISUALIZE_PATH
			mVisitedNodes.push_back(endNodeRecord.node);
#endif
		}

		openList -= current;
		closedList.addBasedOnCost(current);
	}

	if (current.node == pTo)
	{
		NodeRecord temp = current;
		
		while (temp.node != pFrom)
		{
			pPath->addNode(temp.node);
			closedList.find(temp.connection->getFromNode(), temp);
		}

		pPath->addNode(pFrom);
	}

	if (pPath->getNumNodes() == 0)
	{
		delete pPath;
		pPath = nullptr;
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;
}