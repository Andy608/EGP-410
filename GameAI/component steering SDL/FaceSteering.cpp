#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::FACE, ownerID, targetLoc, targetID),
	mAlignSteering(AlignSteering(ownerID, targetLoc, targetID))
{
	
}

Steering* FaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	mAlignSteering.setTargetAngle(atan2(direction.getY(), direction.getX()) - pOwner->getFacing() + (90.0f / 180.0f * 3.14159));

	return mAlignSteering.getSteering();
}
