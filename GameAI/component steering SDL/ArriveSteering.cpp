#include "ArriveSteering.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, float arrivalRadius) :
	Steering(Steering::SteeringType::ARRIVE, ownerID, targetLoc, targetID),
	mArrivalRadius(arrivalRadius)
{
	
}

Steering* ArriveSteering::getSteering()
{
	return this;
}