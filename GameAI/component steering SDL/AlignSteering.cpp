#include <cassert>

#include "AlignSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

AlignSteering::AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::ALIGN, ownerID, targetLoc, targetID),
	mIsTargetAngleGiven(false),
	mTargetAngle(0.0f)
{

}

void AlignSteering::setTargetAngle(const float targetAngle)
{
	mTargetAngle = targetAngle;
	mIsTargetAngleGiven = true;
}

Steering* AlignSteering::getSteering()
{
	static float targetRadius = 0.1f / 180.0f * 3.14159;
	static float slowRadius = 250.0f / 180.0f * 3.14159;
	static float timeToTarget = 0.1f;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float maxRotationalAcc = pOwner->getMaxRotAcc();
	float maxRotationalVel = pOwner->getMaxRotVel();

	float direction;
	float rotationVelocity;
	float targetRotationVelocity;

	//Do we have a valid unit to align with?
	if (mTargetID != INVALID_UNIT_ID)
	{
		//Unit to algin with
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();

		/*
		* If we have a unit to align with, do we want to align with it? 
		* Or did we set the angle somewhere else? (Ex: in the Face Steering class).
		*/
		if (!mIsTargetAngleGiven)
		{
			mTargetAngle = pTarget->getFacing() - pOwner->getFacing() + (90.0f / 180.0f * 3.14159);
		}
	}

	mapToRange(mTargetAngle);
	rotationVelocity = abs(mTargetAngle);

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (rotationVelocity < targetRadius)
	{
		//We are done! Return no steering.
		std::cout << "IN THE TARGET RADIUS!" << std::endl;
		return NULL;
	}

	if (rotationVelocity > slowRadius)
	{
		targetRotationVelocity = maxRotationalVel;
	}
	else
	{
		targetRotationVelocity = maxRotationalVel * rotationVelocity / slowRadius;
	}

	targetRotationVelocity *= mTargetAngle / rotationVelocity;

	data.rotAcc = (targetRotationVelocity - data.rotVel);
	data.rotAcc /= timeToTarget;

	float angularAcc = abs(data.rotAcc);

	if (angularAcc > maxRotationalAcc)
	{
		data.rotAcc /= angularAcc;
		data.rotAcc *= maxRotationalAcc;
	}

	this->mData = data;
	return this;
}

void AlignSteering::mapToRange(float& rotation)
{
	static const float PI = 3.14159;

	if (rotation > PI)
	{
		rotation -= (2 * PI);
	}
	else if (rotation < -PI)
	{
		rotation += (2 * PI);
	}
}