#ifndef ARRIVE_STEERING_H_
#define ARRIVE_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, float arrivalRadius = 1.0f);

protected:
	virtual Steering* getSteering() override;

private:
	float mArrivalRadius;
};

#endif