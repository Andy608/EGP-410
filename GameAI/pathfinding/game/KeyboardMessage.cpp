#include "KeyboardMessage.h"
#include "InputSystem.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "RequestWindowCloseMessage.h"

void KeyboardMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GameMessageManager* pMessageManager = pGame->getMessageManager();

	if (pMessageManager != NULL)
	{
		if (mIsKeyDown)
		{
			if (mIsNewKeyPress)
			{
				if (mInputCode == EnumKeyInput::ESCAPE_KEY)
				{
					pMessageManager->addMessage(new RequestWindowCloseMessage(), 0);
				}
				//A* pathfinding
				else if (mInputCode == EnumKeyInput::A_KEY)
				{
					pGame->setPathfinder(EnumPathfinderType::A_STAR);
				}
				//Dijkstra pathfinding
				else if (mInputCode == EnumKeyInput::D_KEY)
				{
					pGame->setPathfinder(EnumPathfinderType::DIJKSTRA);
				}
				//DFS pathfinding
				else if (mInputCode == EnumKeyInput::F_KEY)
				{
					pGame->setPathfinder(EnumPathfinderType::DFS);
				}
			}
		}
	}
}