#include <stdio.h>
#include <assert.h>

#include <sstream>
#include <SDL.h>

#include <time.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "ComponentManager.h"
#include "UnitManager.h"
#include "InputSystem.h"
#include "SteeringDataModifier.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;
const Uint32 MAX_UNITS = 100;

Game::Game() :
	mpGraphicsSystem(NULL),
	mpGraphicsBufferManager(NULL),
	mpSpriteManager(NULL),
	mpLoopTimer(NULL),
	mpMasterTimer(NULL),
	mpFont(NULL),
	mShouldExit(false),
	mBackgroundBufferID(""),
	mpMessageManager(NULL),
	mpComponentManager(NULL),
	mpUnitManager(NULL),
	mpInputSystem(NULL),
	mpSteeringDataModifier(NULL)
{

}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{	
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	mpSteeringDataModifier = new SteeringDataModifier("steering_data.txt");
	mpSteeringDataModifier->loadData();

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();

	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();

	mpMessageManager = new GameMessageManager();
	mpComponentManager = new ComponentManager(MAX_UNITS);
	mpUnitManager = new UnitManager(MAX_UNITS);
	mpInputSystem = new InputSystem();

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID,"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID,"arrow.png");
	mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID,"enemy_arrow.png");
	mpGraphicsBufferManager->loadBuffer(mTargetBufferID,"target.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);

	if(pBackGroundBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight());
	}
	
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(mPlayerIconBufferID);
	Sprite* pArrowSprite = NULL;
	
	if(pPlayerBuffer != NULL)
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite(PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight());
	}

	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	
	if (pTargetBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	//setup PLAYER
	/*Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	pUnit->setShowTarget(true);
	pUnit->setSteering(Steering::ARRIVE_AND_FACE, ZERO_VECTOR2D);*/

	return true;
}

void Game::cleanup()
{
	if (mpSteeringDataModifier)
	{
		mpSteeringDataModifier->saveData();
	}

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;

	delete mpSpriteManager;
	mpSpriteManager = NULL;
	
	delete mpMessageManager;
	mpMessageManager = NULL;
	
	delete mpUnitManager;
	mpUnitManager = NULL;
	
	delete mpInputSystem;
	mpInputSystem = NULL;
	
	delete mpSteeringDataModifier;
	mpSteeringDataModifier = NULL;
	
	delete mpComponentManager;
	mpComponentManager = NULL;
}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;
	
void Game::processLoop()
{
	mpInputSystem->update();
	mpUnitManager->updateAll(TARGET_ELAPSED_MS);
	mpComponentManager->update(TARGET_ELAPSED_MS);
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	GraphicsBuffer* pDest = mpGraphicsSystem->getBackBuffer();
	mpGraphicsSystem->draw(*pDest, *pBackgroundSprite, 0.0f, 0.0f);

	//draw units
	mpUnitManager->drawAll();

	int x, y;
	mpInputSystem->getMousePosition(x, y);

	//create mouse text
	std::stringstream mousePos;
	mousePos << x << ":" << y;

	//write text at mouse position
	mpGraphicsSystem->writeText(*mpFont, (float)x, (float)y, mousePos.str(), BLACK_COLOR);

	mpGraphicsSystem->swap();

	mpMessageManager->processMessagesForThisframe();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

Vector2D floatToVector2(const float angle)
{
	return Vector2D(cos(angle), sin(angle));
}

void mapRotation(float& rotation)
{
	rotation = fmod(rotation, TAU);

	if (rotation > PI)
	{
		rotation -= TAU;
	}
	else if (rotation < -PI)
	{
		rotation += TAU;
	}
}