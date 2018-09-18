#ifndef WANDER_STEERING_H_
#define WANDER_STEERING_H_

#include <Trackable.h>
#include "Steering.h"
#include "FaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering() override;

	FaceSteering mFaceSteering;
};

#endif