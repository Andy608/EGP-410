#ifndef WANDER_AND_CHASE_STEERING_H_
#define WANDER_AND_CHASE_STEERING_H_

#include <Trackable.h>

#include "Steering.h"
#include "WanderSteering.h"
#include "SeekSteering.h"
#include "FaceSteering.h"

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

protected:
	WanderSteering mWanderSteering;
	SeekSteering mSeekSteering;
	FaceSteering mFaceSteering;

private:
	static const float msWANDER_RADIUS;
};

#endif