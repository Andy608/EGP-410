#include <cassert>

#include "ArriveAndFaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::ARRIVE, ownerID, targetLoc, targetID),
	mArriveSteering(ArriveSteering(ownerID, targetLoc, targetID)),
	mFaceSteering(FaceSteering(ownerID,  targetLoc, targetID))
{

}

Steering* ArriveAndFaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	Steering* arriveSteering = mArriveSteering.getSteering();
	Steering* faceSteering = mFaceSteering.getSteering();

	data.acc = arriveSteering->getData().acc;
	data.rotAcc = faceSteering->getData().rotAcc;

	this->mData = data;
	return this;
}