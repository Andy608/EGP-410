#ifndef GRID_PATHFINDER_H_
#define GRID_PATHFINDER_H_

#include "Pathfinder.h"

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder : public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder(GridGraph* pGraph, Node* pFrom, Node* pTo);
	virtual ~GridPathfinder();

	inline virtual Path* findPath(Node* pFrom, Node* pTo) = 0;
	inline void setNodes(Node* pFrom, Node* pTo) { mpFrom = pFrom; mpTo = pTo; };

	inline Node* getFromNode() const { return mpFrom; }
	inline Node* getToNode() const { return mpTo; }

#ifdef VISUALIZE_PATH
public:
	void drawVisualization(Grid* pGrid, GraphicsBuffer* pDest);

protected:
	std::vector<Node*> mVisitedNodes;
	Path* mpPath;
	GridVisualizer* mpVisualizer;

	Node* mpFrom;
	Node* mpTo;
#endif

	double mTimeElapsed;
};

#endif