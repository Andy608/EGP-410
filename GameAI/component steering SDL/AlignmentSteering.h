#ifndef ALIGNMENT_STEERING_H_
#define ALIGNMENT_STEERING_H_

#include "Steering.h"
#include "AlignSteering.h"

class AlignmentSteering : public Steering
{
public:
	AlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

protected:
	AlignSteering mAlignSteering;

private:
	//Threshold
	const static float msINFLUENCE_RADIUS;
};

#endif