#ifndef WANDER_STEERING_H_
#define WANDER_STEERING_H_

#include "Steering.h"
#include "FaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

protected:
	FaceSteering mFaceSteering;

private:
	static const float msWANDER_OFFSET;
	static const float msWANDER_RADIUS;
	static const float msWANDER_RATE;

	float mWanderOrientation;
	float mTargetOrientation;
};

#endif