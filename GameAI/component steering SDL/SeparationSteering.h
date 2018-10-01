#ifndef SEPARATION_STEERING_H_
#define SEPARATION_STEERING_H_

#include "Steering.h"

class SeparationSteering : public Steering
{
public:
	SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

private:
	//Threshold
	const static float msINFLUENCE_RADIUS;

	/*
	* Decay coefficient
	*  Controls how fast the separation strength
	*  decays with distance.
	*/
	const static float msDECAY_COEFFICIENT;
};


#endif