#include "SettingsFile.h"

const std::string SettingsFile::msINVALID_SETTING_ID = "INVALID SETTING ID";
const std::string SettingsFile::msDELIMITER = "=";

SettingsFile::SettingsFile(const std::string& path) :
	mPATH(path)
{

}

void SettingsFile::setSetting(const std::string& settingID, const std::string& settingKey)
{
	auto mapIter = mSettingData.find(settingID);

	if (mapIter != mSettingData.end())
	{
		mapIter->second = settingKey;
		std::cout << "Set data. Key: " << mapIter->first << " = " << mapIter->second << std::endl;
	}
	else
	{
		if (mSettingData.insert(std::make_pair(settingID, settingKey)).first != mSettingData.end())
		{
			std::cout << "Set data. Key: " << settingID << " = " << settingKey << std::endl;
		}
	}
}

const std::string& SettingsFile::getSetting(const std::string& settingID)
{
	auto mapIter = mSettingData.find(settingID);

	if (mapIter != mSettingData.end())
	{
		return mapIter->second;
	}
	else
	{
		return msINVALID_SETTING_ID;
	}
}

bool SettingsFile::writeDataToFile()
{
	bool success = false;
	mWriteStream.open(mPATH, std::fstream::trunc);

	if (mWriteStream.good())
	{
		auto mapIter = mSettingData.begin();
		for (; mapIter != mSettingData.end(); ++mapIter)
		{
			mWriteStream << mapIter->first << msDELIMITER << mapIter->second << std::endl;
		}

		success = true;
		std::cout << "Saved data to file: \'" << mPATH << "\'";
	}
	else
	{
		std::cout << "Failed to save data to file: \'" << mPATH << "\'";
	}

	mWriteStream.close();
	return success;
}

bool SettingsFile::readDataFromFile()
{
	bool success = false;
	std::string line;
	std::string key;
	std::string value;
	int delimiterIndex;

	mReadStream.open(mPATH, std::ifstream::in);

	if (mReadStream.good())
	{
		mSettingData.clear();

		while (std::getline(mReadStream, line))
		{
			delimiterIndex = line.find_first_of(msDELIMITER);

			if (delimiterIndex != std::string::npos && delimiterIndex != line.size())
			{
				key = line.substr(0, delimiterIndex);
				value = line.substr(delimiterIndex + 1);
				setSetting(key, value);
				success = true;

				std::cout << "Inserted setting from file. Data: " << line << "\'";
			}
			else
			{
				std::cout << "Unable to insert setting from file. Has it been corrupted?" << std::endl;
			}
		}
	}

	mReadStream.close();
	return success;
}