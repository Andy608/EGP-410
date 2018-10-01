#include "AlignmentSteering.h"
#include "Game.h"
#include "UnitManager.h"

const float AlignmentSteering::msINFLUENCE_RADIUS = 10000.0f;

AlignmentSteering::AlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	mAlignSteering(AlignSteering(ownerID, targetLoc, targetID)),
	Steering(Steering::ALIGNMENT, ownerID, targetLoc, targetID)
{

}

Steering* AlignmentSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float maxAcceleration = pOwner->getMaxAcc();

	Vector2D direction = Vector2D();
	float distanceSquared = 0.0f;

	float averageRotation = 0.0f;
	float unitCount = 0.0f;

	const std::map<UnitID, Unit*>& UNITS = gpGame->getUnitManager()->getAllUnits();
	auto unitIter = UNITS.begin();

	for (; unitIter != UNITS.end(); ++unitIter)
	{
		Unit* currentUnit = unitIter->second;

		if (pOwner != currentUnit)
		{
			direction = currentUnit->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distanceSquared = direction.getLengthSquared();

			if (distanceSquared < msINFLUENCE_RADIUS * msINFLUENCE_RADIUS)
			{
				//Arrive at the averaged location
				averageRotation += currentUnit->getFacing();
				++unitCount;
			}
		}
	}

	if (unitCount > 0)
	{
		averageRotation /= unitCount;
		mapRotation(averageRotation);
		mAlignSteering.setTargetAngle(averageRotation);
		mAlignSteering.getSteering();

		data.rotAcc = mAlignSteering.getData().rotAcc;
	}

	this->mData = data;
	return this;
}