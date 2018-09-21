#include "InputSystem.h"
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "Game.h"

#include "KeyboardMessage.h"
#include "MouseMessage.h"
#include "RequestWindowCloseMessage.h"

void InputSystem::update()
{
	while (SDL_PollEvent(&mEventQueue))
	{
		switch (mEventQueue.type)
		{
		case SDL_KEYDOWN:
			//Send keyboard message DOWN
			MESSAGE_MANAGER->addMessage(new KeyboardMessage(mEventQueue.key.keysym.sym, true, mIsNewKeyPress), 0);

			if (mIsNewKeyPress)
			{
				mIsNewKeyPress = false;
			}

			break;
		case SDL_KEYUP:
			//Send keyboard message UP
			MESSAGE_MANAGER->addMessage(new KeyboardMessage(mEventQueue.key.keysym.sym, false, mIsNewKeyPress), 0);
			mIsNewKeyPress = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//Send mouse button message DOWN
			MESSAGE_MANAGER->addMessage(new MouseMessage(mEventQueue.button.button, true, mIsNewMousePress, mEventQueue.button.x, mEventQueue.button.y), 0);
			
			if (mIsNewMousePress)
			{
				mIsNewMousePress = false;
			}
			
			break;
		case SDL_MOUSEBUTTONUP:
			//Send mouse button message UP
			MESSAGE_MANAGER->addMessage(new MouseMessage(mEventQueue.button.button, false, mIsNewMousePress, mEventQueue.button.x, mEventQueue.button.y), 0);
			mIsNewMousePress = true;
			break;
		case SDL_QUIT:
			//Send quit message
			MESSAGE_MANAGER->addMessage(new RequestWindowCloseMessage(), 0);
			break;
		}
	}
}

void InputSystem::getMousePosition(int& x, int& y)
{
	SDL_GetMouseState(&x, &y);
}