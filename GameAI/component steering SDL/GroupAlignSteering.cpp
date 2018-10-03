#include "GroupAlignSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "SteeringDataModifier.h"

const float GroupAlignSteering::msINFLUENCE_RADIUS = 100.0f;

GroupAlignSteering::GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::GROUP_ALIGN, ownerID, targetLoc, targetID),
	mAlignSteering(AlignSteering(ownerID, targetLoc, targetID))
{

}

Steering* GroupAlignSteering::getSteering()
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

			float radius = gpGame->getSteeringDataModifier()->getData(EnumSteeringDataType::ALIGNMENT_RADIUS);
			if (distanceSquared < radius * radius)
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
	else
	{
		data.rotAcc = 0;
		data.rotVel = 0;
	}

	this->mData = data;
	return this;
}