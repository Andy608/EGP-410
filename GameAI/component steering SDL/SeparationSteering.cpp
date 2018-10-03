#include <cassert>

#define NOMINMAX
#include <algorithm>

#include "SeparationSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "SteeringDataModifier.h"

const float SeparationSteering::msINFLUENCE_RADIUS = 75.0f;
const float SeparationSteering::msDECAY_COEFFICIENT = 100000.0f;

SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::SEPARATION, ownerID, targetLoc, targetID)
{

}

Steering* SeparationSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	SteeringDataModifier* pSteeringModifier = gpGame->getSteeringDataModifier();

	float maxAcceleration = pOwner->getMaxAcc();

	Vector2D direction = Vector2D();
	float distanceSquared = 0.0f;
	float strength = 0.0f;
	float unitCount = 0;

	data.rotAcc = 0.0f;

	const std::map<UnitID, Unit*>& UNITS = gpGame->getUnitManager()->getAllUnits();
	auto unitIter = UNITS.begin();

	for (; unitIter != UNITS.end(); ++unitIter)
	{
		Unit* currentUnit = unitIter->second;

		if (pOwner != currentUnit)
		{
			direction = pOwner->getPositionComponent()->getPosition() - currentUnit->getPositionComponent()->getPosition();
			distanceSquared = direction.getLengthSquared();

			float radius = pSteeringModifier->getData(EnumSteeringDataType::SEPARATION_RADIUS);
			if (distanceSquared < radius * radius)
			{
				strength = std::min(pSteeringModifier->getData(EnumSteeringDataType::SEPARATION_DECAY) / distanceSquared, maxAcceleration);
				
				direction.normalize();
				data.acc += (direction * strength);

				++unitCount;
			}
		}
	}

	if (unitCount == 0)
	{
		data.acc = 0;
		data.vel = 0;
	}

	this->mData = data;
	return this;
}