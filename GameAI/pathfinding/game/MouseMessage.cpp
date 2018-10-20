#include "MouseMessage.h"
#include "InputSystem.h"
#include "PathToMessage.h"
#include "GameApp.h"
#include "GameMessageManager.h"

void MouseMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GameMessageManager* pMessageManager = pGame->getMessageManager();

	if (pMessageManager != NULL)
	{
		if (mIsButtonDown)
		{
			//Make path to new unit
			if (mInputCode == EnumMouseInput::LEFT_CLICK)
			{
				static Vector2D lastPos(0.0f, 0.0f);

				if (lastPos.getX() != mMousePosition.getX() || lastPos.getY() != mMousePosition.getY())
				{
					pMessageManager->addMessage(new PathToMessage(lastPos, mMousePosition), 0);
					lastPos = mMousePosition;
				}
			}
		}
	}
}