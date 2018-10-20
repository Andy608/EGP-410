#include "InputSystem.h"
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "GameApp.h"

#include "KeyboardMessage.h"
#include "MouseMessage.h"
#include "RequestWindowCloseMessage.h"

void InputSystem::update()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GameMessageManager* pMessageManager = pGame->getMessageManager();

	if (pMessageManager != NULL)
	{
		while (SDL_PollEvent(&mEventQueue))
		{
			switch (mEventQueue.type)
			{
			case SDL_KEYDOWN:
				//Send keyboard message DOWN
				pMessageManager->addMessage(new KeyboardMessage(mEventQueue.key.keysym.sym, true, mIsNewKeyPress), 0);

				if (mIsNewKeyPress)
				{
					mIsNewKeyPress = false;
				}

				break;
			case SDL_KEYUP:
				//Send keyboard message UP
				pMessageManager->addMessage(new KeyboardMessage(mEventQueue.key.keysym.sym, false, mIsNewKeyPress), 0);
				mIsNewKeyPress = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				//Send mouse button message DOWN
				pMessageManager->addMessage(new MouseMessage(mEventQueue.button.button, true, mIsNewMousePress, mEventQueue.button.x, mEventQueue.button.y), 0);

				if (mIsNewMousePress)
				{
					mIsNewMousePress = false;
				}

				break;
			case SDL_MOUSEBUTTONUP:
				//Send mouse button message UP
				pMessageManager->addMessage(new MouseMessage(mEventQueue.button.button, false, mIsNewMousePress, mEventQueue.button.x, mEventQueue.button.y), 0);
				mIsNewMousePress = true;
				break;
			case SDL_QUIT:
				//Send quit message
				pMessageManager->addMessage(new RequestWindowCloseMessage(), 0);
				break;
			}
		}
	}
}

void InputSystem::getMousePosition(int& x, int& y)
{
	SDL_GetMouseState(&x, &y);
}