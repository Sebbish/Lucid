#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
class SaveLoad
{
	struct saveLoadData
	{
		std::string text;
		int mapID;
	};
public:
	SaveLoad();
	~SaveLoad();
private:
	//std::vector<saveLoadData> mSaveInfo;
	saveLoadData mSLD[5];
};
#endif

