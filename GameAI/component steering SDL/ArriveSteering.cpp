#include <cassert>

#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::ARRIVE, ownerID, targetLoc, targetID)
{
	
}

Steering* ArriveSteering::getSteering()
{
	static float targetRadius = 0.1f;
	static float slowRadius = 200.0f;
	static float timeToTarget = 0.1f;

	Vector2D direction;
	float distance;
	float targetSpeed;
	Vector2D targetVelocity;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	if (mTargetID != INVALID_UNIT_ID)
	{
		//arriving unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (distance < targetRadius)
	{
		//We are done! Return no steering.
		std::cout << "IN THE TARGET RADIUS!" << std::endl;
		return NULL;
	}
	else
	{
		if (distance > slowRadius)
		{
			targetSpeed = pOwner->getMaxSpeed();
		}
		else
		{
			targetSpeed = pOwner->getMaxSpeed() * distance / slowRadius;
		}

		targetVelocity = direction;
		targetVelocity.normalize();
		targetVelocity *= targetSpeed;

		data.acc = targetVelocity - data.vel;
		data.acc /= timeToTarget;

		if (data.acc.getLengthSquared() > pOwner->getMaxAcc() * pOwner->getMaxAcc())
		{
			data.acc.normalize();
			data.acc *= pOwner->getMaxAcc();
		}
	}

	this->mData = data;
	return this;
}