#include "MouseMessage.h"
#include "InputSystem.h"
#include "PathToMessage.h"
#include "GameApp.h"
#include "Grid.h"
#include "GameMessageManager.h"

void MouseMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GameMessageManager* pMessageManager = pGame->getMessageManager();

	if (pMessageManager != NULL)
	{
		if (mIsButtonDown)
		{
			if (mInputCode == EnumMouseInput::LEFT_CLICK)
			{
				static Vector2D lastPos(0.0f, 0.0f);

				if ((lastPos.getX() != mMousePosition.getX() || lastPos.getY() != mMousePosition.getY()) &&
					pGame->getGrid()->getValueAtPixelXY(mMousePosition.getX(), mMousePosition.getY()) != BLOCKING_VALUE)
				{
					pMessageManager->addMessage(new PathToMessage(lastPos, mMousePosition), 0);
					lastPos = mMousePosition;
				}
			}
		}
	}
}