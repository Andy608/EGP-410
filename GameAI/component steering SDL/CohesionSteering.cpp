#include "CohesionSteering.h"

#include "Game.h"
#include "UnitManager.h"

const float CohesionSteering::msINFLUENCE_RADIUS = 200.0f;

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

	this->mData = data;
	return this;
}