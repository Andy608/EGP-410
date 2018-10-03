#ifndef STEERING_DATA_MODIFIER_H_
#define STEERING_DATA_MODIFIER_H_

#include <Trackable.h>
#include "SettingsFile.h"

enum EnumSteeringDataType
{
	INVALID_TYPE = -1,
	
	SEPARATION_STRENGTH,
	COHESION_STRENGTH,
	ALIGNMENT_STRENGTH,
	WANDER_STRENGTH,
	
	SEPARATION_DECAY,
	SEPARATION_RADIUS,
	COHESION_RADIUS,
	ALIGNMENT_RADIUS,
	WANDER_RADIUS
};

class SteeringDataModifier : public Trackable
{
public:
	SteeringDataModifier(const std::string& savePath);

	inline void setTarget(EnumSteeringDataType dataType) { mCurrentTarget = dataType; };
	inline EnumSteeringDataType getTarget() const { return mCurrentTarget; };
	
	void modifyData(EnumSteeringDataType dataType, float value);
	float getData(EnumSteeringDataType dataType);

	void saveData();
	void loadData();

private:
	static const std::string msSEPARATION_STRENGTH_ID;
	static const std::string msCOHESION_STRENGTH_ID;
	static const std::string msALIGNMENT_STRENGTH_ID;
	static const std::string msWANDER_STRENGTH_ID;

	static const std::string msSEPARATION_DECAY_ID;
	static const std::string msSEPARATION_RADIUS_ID;
	static const std::string msCOHESION_RADIUS_ID;
	static const std::string msALIGNMENT_RADIUS_ID;
	static const std::string msWANDER_RADIUS_ID;

	EnumSteeringDataType mCurrentTarget;

	SettingsFile mSettingsFile;

	std::string dataToString(EnumSteeringDataType dataType);
	void initSettings();
	void initSetting(const std::string id, const std::string defaultValue);

};

#endif