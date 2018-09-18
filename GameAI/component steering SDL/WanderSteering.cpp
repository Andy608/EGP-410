#include <cassert>

#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::WANDER, ownerID, targetLoc, targetID),
	mFaceSteering(FaceSteering(ownerID, targetLoc, targetID))
{
	
}

Steering* WanderSteering::getSteering()
{
	static const float wanderRadius = 20.0f;
	static const float wanderOffset = 10.0f;

	static const float maxOrientationChange = 180.0f / 180.0f * 3.14159f;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	
	float currentOrientation = pOwner->getFacing();
	float maxAcceleration = pOwner->getMaxAcc();

	float targetOrientation;

	Vector2D ownerDirection = floatToVector2(pOwner->getFacing() - 90.0f / 180.0f * 3.14159);

	currentOrientation += genRandomBinomial() * maxOrientationChange;
	targetOrientation = currentOrientation + pOwner->getFacing() - 90.0f / 180.0f * 3.14159;
	
	mTargetLoc = pOwner->getPositionComponent()->getPosition() + ownerDirection * wanderOffset;
	mTargetLoc += floatToVector2(targetOrientation) * wanderRadius;

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	Steering* faceSteering = mFaceSteering.getSteering();

	//If we've reached the target rotation, this will be null.
	//Otherwise, add the target acceleration.
	if (faceSteering)
	{
		data.rotAcc = faceSteering->getData().rotAcc;
	}

	data.acc = ownerDirection * maxAcceleration;
	this->mData = data;

	return this;
}
