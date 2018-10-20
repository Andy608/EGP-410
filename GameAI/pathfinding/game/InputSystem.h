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

	A_KEY = SDLK_a,
	D_KEY = SDLK_d,
	F_KEY = SDLK_f
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