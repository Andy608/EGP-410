#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

#include "AStarPathfinder.h"
#include "Path.h"
#include "GridGraph.h"
#include "Game.h"

#include "Heuristic.h"
#include "PathfindingList.h"

AStarPathfinder::AStarPathfinder(Graph* pGraph, Node* pFrom, Node* pTo) :
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

AStarPathfinder::~AStarPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	setNodes(pFrom, pTo);

	Heuristic heuristic = Heuristic(pTo);
	NodeRecord startRecord = NodeRecord(pFrom, nullptr, 0.0f, heuristic.estimateCost(pFrom));

	PathfindingList openList;
	openList += startRecord;

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
		//std::cout << "OPENLIST SIZE: " << std::to_string(openList.size()) << std::endl;

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
			float endNodeHeuristic;
			NodeRecord endNodeRecord;

			if (closedList.contains(endNode))
			{
				closedList.find(endNode, endNodeRecord);

				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					continue;
				}

				closedList -= endNodeRecord;

				endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;
			}
			else if (openList.contains(endNode))
			{
				openList.find(endNode, endNodeRecord);

				//the book says endNodeRecord->cost. not costSoFar :/
				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					continue;
				}

				endNodeHeuristic = endNodeRecord.connection->getCost() - endNodeRecord.costSoFar;
			}
			else
			{
				endNodeRecord = NodeRecord();
				endNodeRecord.node = endNode;

				endNodeHeuristic = heuristic.estimateCost(endNode);
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = currentConnection;
			endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;

			if (!openList.contains(endNode))
			{
				openList += endNodeRecord;
			}

#ifdef VISUALIZE_PATH
			mVisitedNodes.push_back(endNodeRecord.node);
#endif
		}

		openList -= current;
		closedList += current;
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
		pPath->addNode(pFrom);
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;
}