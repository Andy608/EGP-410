#include "KeyboardMessage.h"
#include "InputSystem.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "SteeringDataModifier.h"
#include "Game.h"

void KeyboardMessage::process()
{
	if (mIsKeyDown)
	{
		if (mIsNewKeyPress)
		{
			if (mInputCode == EnumKeyInput::ESCAPE_KEY)
			{
				//Exit game
				gpGame->setShouldClose(true);
			}
			else if (mInputCode == EnumKeyInput::A_KEY)
			{
				//Add 10 unit at random locations
				gpGame->getUnitManager()->createRandomUnits(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), 10);
			}
			else if (mInputCode == EnumKeyInput::D_KEY)
			{
				//Delete random unit
				gpGame->getUnitManager()->deleteRandomUnit();
			}
			else if (mInputCode == EnumKeyInput::ONE_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::SEPARATION_STRENGTH);
			}
			else if (mInputCode == EnumKeyInput::TWO_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::COHESION_STRENGTH);
			}
			else if (mInputCode == EnumKeyInput::THREE_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::ALIGNMENT_STRENGTH);
			}
			else if (mInputCode == EnumKeyInput::FOUR_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::WANDER_STRENGTH);
			}
			else if (mInputCode == EnumKeyInput::FIVE_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::SEPARATION_DECAY);
			}
			else if (mInputCode == EnumKeyInput::SIX_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::SEPARATION_RADIUS);
			}
			else if (mInputCode == EnumKeyInput::SEVEN_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::COHESION_RADIUS);
			}
			else if (mInputCode == EnumKeyInput::EIGHT_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::ALIGNMENT_RADIUS);
			}
			else if (mInputCode == EnumKeyInput::NINE_KEY)
			{
				gpGame->getSteeringDataModifier()->setTarget(EnumSteeringDataType::WANDER_RADIUS);
			}
		}

		//Up increases selected item
		if (mInputCode == EnumKeyInput::UP_KEY)
		{
			SteeringDataModifier* steeringModifier = gpGame->getSteeringDataModifier();
			steeringModifier->modifyData(steeringModifier->getTarget(), 0.1f);
		}
		//Down decreases selected item
		else if (mInputCode == EnumKeyInput::DOWN_KEY)
		{
			SteeringDataModifier* steeringModifier = gpGame->getSteeringDataModifier();
			steeringModifier->modifyData(steeringModifier->getTarget(), -0.1f);
		}
	}
}