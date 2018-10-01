#include "FlockSteering.h"
#include "Game.h"
#include "UnitManager.h"

const int FlockSteering::msBEHAVIOR_LENGTH = 3;

FlockSteering::FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::FLOCK, ownerID, targetLoc, targetID),
	mpBehaviors(new BehaviorAndWeight[msBEHAVIOR_LENGTH]),
	mSeparationSteering(SeparationSteering(ownerID, targetLoc, targetID)),
	mCohesionSteering(CohesionSteering(ownerID, targetLoc, targetID)),
	mGroupAlignSteering(GroupAlignSteering(ownerID, targetLoc, targetID))
{
	mpBehaviors[0] = BehaviorAndWeight(&mSeparationSteering, 5.0f);
	mpBehaviors[1] = BehaviorAndWeight(&mCohesionSteering, 1.0f);
	mpBehaviors[2] = BehaviorAndWeight(&mGroupAlignSteering, 0.0f);
}

FlockSteering::~FlockSteering()
{
	if (mpBehaviors)
	{
		delete[] mpBehaviors;
		mpBehaviors = nullptr;
	}
}

Steering* FlockSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float maxAcceleration = pOwner->getMaxAcc();
	float maxRotAcceleration = pOwner->getMaxRotAcc();

	Steering* blendedSteering = this;
	int i = 0;

	for (; i < msBEHAVIOR_LENGTH; ++i)
	{
		BehaviorAndWeight currentBehavior = mpBehaviors[i];
		data.acc += currentBehavior.mSteering->getSteering()->getData().acc * currentBehavior.mWeight;
		data.rotAcc += currentBehavior.mSteering->getSteering()->getData().rotAcc * currentBehavior.mWeight;
	}

	if (data.acc.getLength() < maxAcceleration)
	{
		data.acc.normalize();
		data.acc *= maxAcceleration;
	}

	/*if (data.acc.getLength() != 0.0f && data.rotAcc < maxRotAcceleration)
	{
		data.rotAcc = maxRotAcceleration;
	}*/

	this->mData = data;
	return this;
}