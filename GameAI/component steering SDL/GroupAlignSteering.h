#ifndef GROUP_ALIGN_STEERING_H_
#define GROUP_ALIGN_STEERING_H_

#include "Steering.h"
#include "AlignSteering.h"

class GroupAlignSteering : public Steering
{
public:
	GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

protected:
	AlignSteering mAlignSteering;

private:
	//Threshold
	const static float msINFLUENCE_RADIUS;
};

#endif