#ifndef GAME_H_
#define GAME_H_

#include <string>

#include <Trackable.h>
#include <PerformanceTracker.h>
#include "Defines.h"

class GraphicsSystem;
class GraphicsBuffer;
class Font;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;
class ComponentManager;
class UnitManager;
class Vector2D;
class InputSystem;
class SteeringDataModifier;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType TARGET_SPRITE_ID = 3;

//how long should each frame of execution take? 30fps = 33.3ms/frame
const float LOOP_TARGET_TIME = 33.3f;

class Game : public Trackable
{
public:
	Game();
	~Game();

	//returns true if no errors, false otherwise
	bool init();
	void cleanup();

	void setShouldClose(bool shouldClose) { mShouldExit = shouldClose; };

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	//getters
	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline ComponentManager* getComponentManager() { return mpComponentManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline InputSystem* getInputSystem() { return mpInputSystem; };
	inline SteeringDataModifier* getSteeringDataModifier() { return mpSteeringDataModifier; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	ComponentManager* mpComponentManager;
	UnitManager* mpUnitManager;
	InputSystem* mpInputSystem;
	SteeringDataModifier* mpSteeringDataModifier;
	Font* mpFont;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;

	//should be somewhere else
	GraphicsBufferID mBackgroundBufferID = "woods";
	GraphicsBufferID mPlayerIconBufferID = "player";
	GraphicsBufferID mEnemyIconBufferID = "enemy";
	GraphicsBufferID mTargetBufferID = "target";

};

//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomBinomial();

//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();

//Returns a vector based on the angle.
Vector2D floatToVector2(const float angle);

//Map rotation to stay inside the circle.
void mapRotation(float& rotation);

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

#endif