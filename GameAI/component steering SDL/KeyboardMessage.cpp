#include "KeyboardMessage.h"
#include "InputSystem.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "Game.h"

void KeyboardMessage::process()
{
	if (mIsKeyDown && mIsNewKeyPress)
	{
		if (mInputCode == EnumKeyInput::ESCAPE_KEY)
		{
			//Exit game
			gpGame->setShouldClose(true);
		}
		else if (mInputCode == EnumKeyInput::ENTER_KEY)
		{
			//Add unit at random location
			Unit* pUnit = gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID));

			if (pUnit == NULL)
			{
				gpGame->getUnitManager()->deleteRandomUnit();
			}
		}
		else if (mInputCode == EnumKeyInput::D_KEY)
		{
			//Delete random unit
			gpGame->getUnitManager()->deleteRandomUnit();
		}
	}
}