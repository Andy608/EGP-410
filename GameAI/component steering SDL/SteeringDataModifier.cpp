#include "SteeringDataModifier.h"

#include "FlockSteering.h"

const std::string SteeringDataModifier::msSEPARATION_STRENGTH_ID = "separation_strength";
const std::string SteeringDataModifier::msCOHESION_STRENGTH_ID = "cohesion_strength";
const std::string SteeringDataModifier::msALIGNMENT_STRENGTH_ID = "alignment_strength";
const std::string SteeringDataModifier::msWANDER_STRENGTH_ID = "wander_strength";

const std::string SteeringDataModifier::msSEPARATION_DECAY_ID = "separation_decay";
const std::string SteeringDataModifier::msSEPARATION_RADIUS_ID = "separation_radius";
const std::string SteeringDataModifier::msCOHESION_RADIUS_ID = "cohesion_radius";
const std::string SteeringDataModifier::msALIGNMENT_RADIUS_ID = "alignment_radius";
const std::string SteeringDataModifier::msWANDER_RADIUS_ID = "wander_radius";

SteeringDataModifier::SteeringDataModifier(const std::string& savePath) :
	mSettingsFile(SettingsFile(savePath)),
	mCurrentTarget(INVALID_TYPE)
{
	initSettings();
}

void SteeringDataModifier::modifyData(EnumSteeringDataType dataType, float offset)
{
	if (dataType != INVALID_TYPE)
	{
		mSettingsFile.setSetting(dataToString(dataType), std::to_string(offset + getData(dataType)));
	}
}

float SteeringDataModifier::getData(EnumSteeringDataType dataType)
{
	float dataAsFloat = 0.0f;

	if (dataType != INVALID_TYPE)
	{
		std::string data = mSettingsFile.getSetting(dataToString(dataType));

		try
		{
			dataAsFloat = std::stof(data);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "Unable to convert data. Not a valid number: " << e.what();
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "Unable to convert data. Out of range: " << e.what();
		}
	}

	return dataAsFloat;
}

void SteeringDataModifier::saveData()
{
	mSettingsFile.writeDataToFile();
}

void SteeringDataModifier::loadData()
{
	mSettingsFile.readDataFromFile();
}

std::string SteeringDataModifier::dataToString(EnumSteeringDataType dataType)
{
	std::string modifier;

	switch (dataType)
	{
	case SEPARATION_STRENGTH:
		modifier = msSEPARATION_STRENGTH_ID;
		break;
	case COHESION_STRENGTH:
		modifier = msCOHESION_STRENGTH_ID;
		break;
	case ALIGNMENT_STRENGTH:
		modifier = msALIGNMENT_STRENGTH_ID;
		break;
	case WANDER_STRENGTH:
		modifier = msWANDER_STRENGTH_ID;
		break;
	case SEPARATION_DECAY:
		modifier = msSEPARATION_DECAY_ID;
		break;
	case SEPARATION_RADIUS:
		modifier = msSEPARATION_RADIUS_ID;
		break;
	case COHESION_RADIUS:
		modifier = msCOHESION_RADIUS_ID;
		break;
	case ALIGNMENT_RADIUS:
		modifier = msALIGNMENT_RADIUS_ID;
		break;
	case WANDER_RADIUS:
		modifier = msWANDER_RADIUS_ID;
		break;
	default:
		modifier = SettingsFile::msINVALID_SETTING_ID;
	}

	return modifier;
}

void SteeringDataModifier::initSettings()
{
	initSetting(msSEPARATION_STRENGTH_ID, std::to_string(FlockSteering::msSEPARATION_STRENGTH));
	initSetting(msCOHESION_STRENGTH_ID, std::to_string(FlockSteering::msCOHESION_STRENGTH));
	initSetting(msALIGNMENT_STRENGTH_ID, std::to_string(FlockSteering::msALIGNMENT_STRENGTH));
	initSetting(msWANDER_STRENGTH_ID, std::to_string(FlockSteering::msWANDER_STRENGTH));
	initSetting(msSEPARATION_DECAY_ID, std::to_string(SeparationSteering::msDECAY_COEFFICIENT));
	initSetting(msSEPARATION_RADIUS_ID, std::to_string(SeparationSteering::msINFLUENCE_RADIUS));
	initSetting(msCOHESION_RADIUS_ID, std::to_string(CohesionSteering::msINFLUENCE_RADIUS));
	initSetting(msALIGNMENT_RADIUS_ID, std::to_string(GroupAlignSteering::msINFLUENCE_RADIUS));
	initSetting(msWANDER_RADIUS_ID, std::to_string(WanderSteering::msWANDER_RADIUS));
}

void SteeringDataModifier::initSetting(const std::string id, const std::string defaultValue)
{
	if (mSettingsFile.getSetting(id) == SettingsFile::msINVALID_SETTING_ID)
	{
		mSettingsFile.setSetting(id, defaultValue);
	}
}