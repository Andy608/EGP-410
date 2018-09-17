#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::FACE, ownerID, targetLoc, targetID)
{

}

Steering* FaceSteering::getSteering()
{
	static float targetRadius = 0.1f / 180.0f * 3.14159;
	static float slowRadius = 250.0f / 180.0f * 3.14159;
	static float timeToTarget = 0.1f;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	
	float maxRotationalAcc = pOwner->getMaxRotAcc();
	float maxRotationalVel = pOwner->getMaxRotVel();

	Vector2D direction;
	float angle;
	float rotationVelocity;
	float targetRotationVelocity;

	if (mTargetID != INVALID_UNIT_ID)
	{
		//Unit to face
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	angle = atan2(direction.getY(), direction.getX()) - pOwner->getFacing() + (90.0f / 180.0f * 3.14159);
	mapToRange(angle);
	rotationVelocity = abs(angle);

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

	targetRotationVelocity *= angle / rotationVelocity;

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

void FaceSteering::mapToRange(float& rotation)
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