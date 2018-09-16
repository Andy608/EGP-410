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
	if (mTargetID != INVALID_UNIT_ID)
	{
		//arriving unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	
	float targetRadius = 50.0f;
	float timeToTarget = 0.1f;

	float maxRotAcc = pOwner->getMaxRotAcc();
	float maxRotation = 360.0f;
	
	//The rotation we need to get to.
	Vector2D targetRotationVec = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	//The current and target rotation radians
	float currentRotation = pOwner->getFacing();
	float targetRotation = atan2(targetRotationVec.getY(), targetRotationVec.getX()) /*+ (3.14159 / 2.0f)*/;

	float rotationDirection;

	std::cout << "TARGET ROTATION: " << std::to_string(targetRotation) << std::endl;

	PhysicsData data = pOwner->getPhysicsComponent()->getData();



	/*float velDirection = atan2(velocity.getY(), velocity.getX()) + (3.14159 / 2.0f);
	pOwner->getPositionComponent()->setFacing(velDirection);*/

	//data.vel = velocity;
	data.rotVel = 0.0f;
	this->mData = data;
	return this;
}