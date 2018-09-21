#include <cassert>

#include "WanderAndChaseSteering.h"
#include "Game.h"
#include "UnitManager.h"

const float WanderAndChaseSteering::msWANDER_RADIUS = 200.0f;

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::WANDER, ownerID, targetLoc, targetID),
	mWanderSteering(WanderSteering(ownerID, targetLoc, targetID)),
	mSeekSteering(SeekSteering(ownerID, targetLoc, targetID)),
	mFaceSteering(FaceSteering(ownerID, targetLoc, targetID))
{

}

Steering* WanderAndChaseSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	Steering* steering = nullptr;

	Vector2D playerLoc = gpGame->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();

	Vector2D distance = playerLoc - pOwner->getPositionComponent()->getPosition();

	if (distance.getLengthSquared() > msWANDER_RADIUS * msWANDER_RADIUS)
	{
		steering = mWanderSteering.getSteering();

		data.rotAcc = steering->getData().rotAcc;
	}
	else
	{
		mSeekSteering.setTargetLoc(playerLoc);
		steering = mSeekSteering.getSteering();

		mFaceSteering.setTargetLoc(playerLoc);
		data.rotAcc = mFaceSteering.getSteering()->getData().rotAcc;
	}

	data.acc = steering->getData().acc;

	this->mData = data;
	return this;
}