#ifndef COHESION_STEERING_H_
#define COHESION_STEERING_H_

#include "Steering.h"
#include "ArriveSteering.h"

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	virtual Steering* getSteering() override;

protected:
	ArriveSteering mArriveSteering;

private:
	//Threshold
	const static float msINFLUENCE_RADIUS;
};

#endif