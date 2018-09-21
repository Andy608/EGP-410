#include <cassert>

#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"

const float WanderSteering::msWANDER_OFFSET = 100.0f;
const float WanderSteering::msWANDER_RADIUS = 80.0f;
const float WanderSteering::msWANDER_RATE = 2.0f * 3.14159f;

WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::WANDER, ownerID, targetLoc, targetID),
	mFaceSteering(FaceSteering(ownerID, targetLoc, targetID))
{
	
}

//Steering* WanderSteering::getSteering()
//{
//	static const float wanderRadius = 100.0f;
//	static const float wanderOffset = 0.0f;
//
//	static const float maxOrientationChange = 180.0f / 180.0f * 3.14159f;
//
//	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
//	
//	float wanderOrientation = 0.0f;
//	float maxAcceleration = pOwner->getMaxAcc();
//
//	PhysicsData data = pOwner->getPhysicsComponent()->getData();
//
//	Vector2D ownerDirection = floatToVector2(pOwner->getFacing());
//	
//	Vector2D targetLoc = pOwner->getPositionComponent()->getPosition() + ownerDirection * wanderOffset;
//	targetLoc += floatToVector2(mTargetOrientation) * wanderRadius;
//
//	mFaceSteering.setTargetLoc(targetLoc);
//
//	mTargetLoc = targetLoc;
//
//	Steering* faceSteering = mFaceSteering.getSteering();
//
//	//If it's reached the target angle, pick a new wander orientation.
//	if (!faceSteering)
//	{
//		std::cout << "PICK NEW ORIENTATION." << std::endl;
//		wanderOrientation += genRandomBinomial() * maxOrientationChange;
//		mTargetOrientation = wanderOrientation + pOwner->getFacing();
//	}
//	else
//	{
//		std::cout << "STEERING" << std::endl;
//		data.rotAcc = faceSteering->getData().rotAcc;
//	}
//
//	data.acc = ownerDirection * maxAcceleration;
//	this->mData = data;
//
//	return this;
//}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float maxAcceleration = pOwner->getMaxAcc();

	mWanderOrientation += genRandomBinomial() * msWANDER_RATE;
	mTargetOrientation = mWanderOrientation + pOwner->getFacing();

	Vector2D ownerDirection = floatToVector2(pOwner->getFacing());
	ownerDirection.normalize();

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + ownerDirection * msWANDER_OFFSET;
	mTargetLoc += floatToVector2(mTargetOrientation) * msWANDER_RADIUS;
	
	mFaceSteering.setTargetLoc(mTargetLoc);

	Steering* faceSteering = mFaceSteering.getSteering();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	data.rotAcc = faceSteering->getData().rotAcc;
	data.acc = ownerDirection * maxAcceleration;
	
	this->mData = data;
	return this;
}