#include "MouseMessage.h"
#include "InputSystem.h"
#include "UnitManager.h"
#include "Game.h"

void MouseMessage::process()
{
	if (mIsButtonDown)
	{
		if (mInputCode == EnumMouseInput::LEFT_CLICK)
		{
			//Steer player to clicked position.
			Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
			pPlayer->setSteering(Steering::ARRIVE_AND_FACE, mMousePosition);
		}
	}
}