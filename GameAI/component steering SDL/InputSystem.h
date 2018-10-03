#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include <SDL.h>
#include <SDL_keycode.h>
#include <Vector2D.h>
#include <Trackable.h>

enum EnumMouseInput
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 4
};

enum EnumKeyInput
{
	ESCAPE_KEY = SDLK_ESCAPE,
	ENTER_KEY = SDLK_RETURN,
	
	A_KEY = SDLK_a,			//Spawns 10 random units
	D_KEY = SDLK_d,			//Deletes random unit

	UP_KEY = SDLK_UP,		//Values go down
	DOWN_KEY = SDLK_DOWN,	//Values go up
	
	ONE_KEY = SDLK_1,		//Selection strength
	TWO_KEY = SDLK_2,		//Cohesion strength
	THREE_KEY = SDLK_3,		//Alignment strength
	FOUR_KEY = SDLK_4,		//Wander strength
	FIVE_KEY = SDLK_5,		//Selection coef
	SIX_KEY = SDLK_6,		//Selection radius
	SEVEN_KEY = SDLK_7,		//Cohesion radius
	EIGHT_KEY = SDLK_8,		//Alignment radius
	NINE_KEY = SDLK_9		//Wander radius
};

class InputSystem : public Trackable
{
public:
	inline InputSystem() {};
	inline ~InputSystem() {};

	void update();

	void getMousePosition(int& x, int& y);

private:
	SDL_Event mEventQueue;
	bool mIsMouseDown = false;
	bool mIsNewMousePress = true;
	bool mIsNewKeyPress = true;
};

#endif