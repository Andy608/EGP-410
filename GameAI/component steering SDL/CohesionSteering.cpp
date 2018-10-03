#include "CohesionSteering.h"

#include "Game.h"
#include "UnitManager.h"
#include "SteeringDataModifier.h"

const float CohesionSteering::msINFLUENCE_RADIUS = 100.0f;

CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::COHESION, ownerID, targetLoc, targetID),
	mArriveSteering(ArriveSteering(ownerID, targetLoc, targetID))
{

}

Steering* CohesionSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float maxAcceleration = pOwner->getMaxAcc();

	Vector2D direction = Vector2D();
	float distanceSquared = 0.0f;

	Vector2D averagePosition;
	float unitCount = 0;

	data.rotAcc = 0.0f;

	const std::map<UnitID, Unit*>& UNITS = gpGame->getUnitManager()->getAllUnits();
	auto unitIter = UNITS.begin();

	for (; unitIter != UNITS.end(); ++unitIter)
	{
		Unit* currentUnit = unitIter->second;

		if (pOwner != currentUnit)
		{
			direction = currentUnit->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distanceSquared = direction.getLengthSquared();

			float radius = gpGame->getSteeringDataModifier()->getData(EnumSteeringDataType::COHESION_RADIUS);
			if (distanceSquared < radius * radius)
			{
				//Arrive at the averaged location
				averagePosition += currentUnit->getPositionComponent()->getPosition();
				++unitCount;
			}
		}
	}

	if (unitCount > 0)
	{
		averagePosition /= unitCount;
		mArriveSteering.setTargetLoc(averagePosition);
		mArriveSteering.getSteering();

		data.acc = mArriveSteering.getData().acc;
	}
	else
	{
		data.acc = 0;
		data.vel = 0;
	}

	this->mData = data;
	return this;
}