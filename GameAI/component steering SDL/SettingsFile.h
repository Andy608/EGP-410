#ifndef SETTINGS_FILE_H_
#define SETTINGS_FILE_H_

#include <Trackable.h>
#include <map>
#include <fstream>
#include <sstream>

/*
* Responsible for:
* - reading data from a file and storing it in a map for easy access.
* - populate file with data stored in the map.
*/
class SettingsFile : public Trackable
{
public:
	static const std::string msINVALID_SETTING_ID;

	SettingsFile(const std::string& path);

	void setSetting(const std::string& settingID, const std::string& settingKey);
	const std::string& getSetting(const std::string& settingID);

	bool writeDataToFile();
	bool readDataFromFile();

private:
	static const std::string msDELIMITER;

	const std::string mPATH;
	
	std::ifstream mReadStream;
	std::stringstream mStringStream;
	std::ofstream mWriteStream;

	std::map<std::string, std::string> mSettingData;
};

#endif