#include <cassert>

#include "Steering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


SeekSteering::SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee) : 
	Steering(getSteeringType(shouldFlee), ownerID, targetLoc, targetID) 
{

}

Steering* SeekSteering::getSteering()
{
	Vector2D distance;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//are we seeking a location or a unit?
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::SEEK)
	{
		distance = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		distance = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	distance.normalize();
	distance *= pOwner->getMaxAcc();

	data.acc = distance;
	this->mData = data;
	return this;
}

