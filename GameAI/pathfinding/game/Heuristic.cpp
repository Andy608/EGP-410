#include "Heuristic.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridGraph.h"
#include <Vector2D.h>

float Heuristic::estimateCost(Node* startNode)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	if (pGame != NULL)
	{
		GridPathfinder* pPathfinder = pGame->getPathfinder();
		GridGraph* pGridGraph = pGame->getGridGraph();
		Grid* pGrid = pGame->getGrid();

		Vector2D fromGridPos = pGrid->getULCornerOfSquare(startNode->getId());
		Vector2D toGridPos = pGrid->getULCornerOfSquare(mGoalNode->getId());
		Vector2D dist = toGridPos - fromGridPos;

		return dist.getLengthSquared();
	}

	std::cout << "The game hasn't been initialized yet. Cannot estimate heuristic." << std::endl;
	return 0.0f;
}