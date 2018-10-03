#include <cassert>

#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "SteeringDataModifier.h"

const float WanderSteering::msWANDER_OFFSET = 40.0f;
const float WanderSteering::msWANDER_RADIUS = 80.0f;
const float WanderSteering::msWANDER_RATE = TAU;

WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::WANDER, ownerID, targetLoc, targetID),
	mFaceSteering(FaceSteering(ownerID, targetLoc, targetID)),
	mWanderOrientation(0)
{

}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float maxAcceleration = pOwner->getMaxAcc();

	mWanderOrientation += genRandomBinomial() * msWANDER_RATE;
	mTargetOrientation = mWanderOrientation + pOwner->getFacing();

	Vector2D ownerDirection = floatToVector2(pOwner->getFacing());

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + ownerDirection * msWANDER_OFFSET;
	mTargetLoc += floatToVector2(mTargetOrientation) * gpGame->getSteeringDataModifier()->getData(EnumSteeringDataType::WANDER_RADIUS);
	
	mFaceSteering.setTargetLoc(mTargetLoc);

	Steering* faceSteering = mFaceSteering.getSteering();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	data.rotAcc = faceSteering->getData().rotAcc;
	data.acc = ownerDirection * maxAcceleration;
	
	this->mData = data;
	return this;
}