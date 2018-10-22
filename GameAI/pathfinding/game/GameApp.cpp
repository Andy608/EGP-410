#include "Game.h"
#include "GameApp.h"
#include "InputSystem.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <Vector2D.h>
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"

#include <SDL.h>
#include <fstream>
#include <vector>

const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

GameApp::GameApp() : 
	mpInputSystem(nullptr),
	mpMessageManager(nullptr),
	mpGrid(nullptr),
	mpGridGraph(nullptr),
	mpPathfinder(nullptr),
	mpDebugDisplay(nullptr)
{

}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if (retVal == false)
	{
		return false;
	}

	mpInputSystem = new InputSystem();
	mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer(mpGrid);

	std::ifstream theStream(gFileName);
	mpGrid->load(theStream);

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);

	//init the nodes and connections
	mpGridGraph->init();

	setPathfinder(EnumPathfinderType::DFS);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);
	if(pBackGroundBuffer != nullptr)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight());
	}

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpInputSystem;
	mpInputSystem = nullptr;

	delete mpMessageManager;
	mpMessageManager = nullptr;

	delete mpGrid;
	mpGrid = nullptr;

	delete mpGridVisualizer;
	mpGridVisualizer = nullptr;

	delete mpGridGraph;
	mpGridGraph = nullptr;

	delete mpDebugDisplay;
	mpDebugDisplay = nullptr;

	delete mpPathfinder;
	mpPathfinder = nullptr;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif

	mpDebugDisplay->draw(pBackBuffer);

	mpInputSystem->update();
	mpMessageManager->processMessagesForThisframe();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

void GameApp::setPathfinder(EnumPathfinderType type)
{
	Node* pFrom = nullptr;
	Node* pTo = nullptr;

	if (mpPathfinder)
	{
		pFrom = mpPathfinder->getFromNode();
		pTo = mpPathfinder->getToNode();
		delete mpPathfinder;
	}

	switch (type)
	{
	case EnumPathfinderType::DFS:
		mpPathfinder = new DepthFirstPathfinder(mpGridGraph, pFrom, pTo);
		break;
	case EnumPathfinderType::DIJKSTRA:
		mpPathfinder = new DijkstraPathfinder(mpGridGraph, pFrom, pTo);
		break;
	case EnumPathfinderType::A_STAR:
		mpPathfinder = new AStarPathfinder(mpGridGraph, pFrom, pTo);
		break;
	}

	if (mpDebugDisplay)
	{
		delete mpDebugDisplay;
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}