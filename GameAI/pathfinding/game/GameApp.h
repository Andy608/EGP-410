#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class InputSystem;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;

class AStarPathfinder;
class DepthFirstPathfinder;
class DijkstraPathfinder;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

enum EnumPathfinderType
{
	DFS,
	DIJKSTRA,
	A_STAR
};

class GameApp : public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void setPathfinder(EnumPathfinderType type);

	//accessors
	inline InputSystem* getInputSystem() { return mpInputSystem; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };

private:
	InputSystem* mpInputSystem;
	GameMessageManager* mpMessageManager;
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;

	GridPathfinder* mpPathfinder;
};

