#ifndef ALIGN_STEERING_H_
#define ALIGN_STEERING_H_

#include <Trackable.h>
#include "Steering.h"

class AlignSteering : public Steering
{
public:
	AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	void setTargetAngle(const float targetAngle);
	virtual Steering* getSteering() override;

protected:
	bool mIsTargetAngleGiven;
	float mTargetAngle;

private:
	//Maps the rotation between -PI and PI.
	void mapToRange(float& rotation);
};

#endif