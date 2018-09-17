#ifndef FACE_STEERING_H_
#define FACE_STEERING_H_

#include <Trackable.h>
#include "AlignSteering.h"

class FaceSteering : public AlignSteering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering() override;
};

#endif