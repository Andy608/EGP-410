#include <cassert>

#define NOMINMAX
#include <algorithm>

#include "SeparationSteering.h"
#include "Game.h"
#include "UnitManager.h"

const float SeparationSteering::msINFLUENCE_RADIUS = 300.0f;
const float SeparationSteering::msDECAY_COEFFICIENT = 100.0f;

SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::SEPARATION, ownerID, targetLoc, targetID)
{

}

Steering* SeparationSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float maxAcceleration = pOwner->getMaxAcc();

	Vector2D direction = Vector2D();
	float distanceSquared = 0.0f;
	float strength = 0.0f;

	const std::map<UnitID, Unit*>& UNITS = gpGame->getUnitManager()->getAllUnits();
	auto unitIter = UNITS.begin();

	for (; unitIter != UNITS.end(); ++unitIter)
	{
		Unit* currentUnit = unitIter->second;

		if (pOwner != currentUnit)
		{
			direction = unitIter->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distanceSquared = direction.getLengthSquared();

			if (distanceSquared < msINFLUENCE_RADIUS * msINFLUENCE_RADIUS)
			{
				strength = std::min(msDECAY_COEFFICIENT / distanceSquared, maxAcceleration);
				
				direction.normalize();
				data.acc += direction * strength;
			}
		}
	}

	this->mData = data;
	return this;
}