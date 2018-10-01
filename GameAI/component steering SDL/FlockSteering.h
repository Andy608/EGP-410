#ifndef FLOCK_STEERING_H_
#define FLOCK_STEERING_H_

#include "Steering.h"
#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignSteering.h"

struct BehaviorAndWeight : public Trackable
{
	inline BehaviorAndWeight(Steering* steering = nullptr, float weight = 0.0f) : mSteering(steering), mWeight(weight) {};

	Steering* mSteering;
	float mWeight;
};

class FlockSteering : public Steering
{
public:
	FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	~FlockSteering();

	virtual Steering* getSteering() override;

protected:
	static const int msBEHAVIOR_LENGTH;
	BehaviorAndWeight* mpBehaviors;

	SeparationSteering mSeparationSteering;
	CohesionSteering mCohesionSteering;
	GroupAlignSteering mGroupAlignSteering;
};

#endif