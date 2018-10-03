#include "MouseMessage.h"
#include "InputSystem.h"
#include "UnitManager.h"
#include "Game.h"
#include "SpriteManager.h"

void MouseMessage::process()
{
	if (mIsButtonDown)
	{
		if (mInputCode == EnumMouseInput::LEFT_CLICK)
		{
			//Steer player to clicked position.
			Unit* pUnit = gpGame->getUnitManager()->createUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), true, PositionData(Vector2D(mMousePosition.getX(), mMousePosition.getY()), 0));
			pUnit->setSteering(Steering::FLOCK);

			if (pUnit == NULL)
			{
				gpGame->getUnitManager()->deleteRandomUnit();
			}
		}
	}
}