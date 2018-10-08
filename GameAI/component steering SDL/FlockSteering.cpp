#include "FlockSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "SteeringDataModifier.h"

const float FlockSteering::msSEPARATION_STRENGTH = 1.0f;
const float FlockSteering::msCOHESION_STRENGTH = 0.7f;
const float FlockSteering::msALIGNMENT_STRENGTH = 1.0f;
const float FlockSteering::msWANDER_STRENGTH = 1.0f;

const int FlockSteering::msBEHAVIOR_LENGTH = 4;

FlockSteering::FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::FLOCK, ownerID, targetLoc, targetID),
	mpBehaviors(new BehaviorAndWeight[msBEHAVIOR_LENGTH]),
	mSeparationSteering(SeparationSteering(ownerID, targetLoc, targetID)),
	mCohesionSteering(CohesionSteering(ownerID, targetLoc, targetID)),
	mGroupAlignSteering(GroupAlignSteering(ownerID, targetLoc, targetID)),
	mWanderSteering(WanderSteering(ownerID, targetLoc, targetID))
{
	SteeringDataModifier* steeringModifier = gpGame->getSteeringDataModifier();
	mpBehaviors[0] = BehaviorAndWeight(&mSeparationSteering, steeringModifier->getData(EnumSteeringDataType::SEPARATION_STRENGTH));
	mpBehaviors[1] = BehaviorAndWeight(&mCohesionSteering, steeringModifier->getData(EnumSteeringDataType::COHESION_STRENGTH));
	mpBehaviors[2] = BehaviorAndWeight(&mGroupAlignSteering, steeringModifier->getData(EnumSteeringDataType::ALIGNMENT_STRENGTH));
	mpBehaviors[3] = BehaviorAndWeight(&mWanderSteering, steeringModifier->getData(EnumSteeringDataType::WANDER_STRENGTH));
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

	data.acc = 0;
	data.rotAcc = 0;

	int i = 0;

	for (; i < msBEHAVIOR_LENGTH; ++i)
	{
		BehaviorAndWeight currentBehavior = mpBehaviors[i];
		Steering* steering = currentBehavior.mSteering->getSteering();
		data.acc += (steering->getData().acc * currentBehavior.mWeight);
		data.rotAcc += (steering->getData().rotAcc * currentBehavior.mWeight);
	}

	data.acc.normalize();
	data.acc *= maxAcceleration;

	this->mData = data;
	return this;
}