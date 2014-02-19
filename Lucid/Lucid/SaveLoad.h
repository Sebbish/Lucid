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
	public:
		std::string text;
		int mapID;
	};
public:
	SaveLoad();
	~SaveLoad();
	void save(int activeSlot, std::string name, int mapID);
	int load(int activeSlot)const;
	std::string loadText(int slot);
private:
	saveLoadData mSLD[5];
	std::ofstream sstream;
	std::fstream stream;
};
#endif

