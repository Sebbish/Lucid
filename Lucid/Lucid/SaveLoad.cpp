#include "SaveLoad.h"


SaveLoad::SaveLoad()
{
	
	stream.open("../Debug/SaveFile.txt");
	if(!stream.is_open())
	{
		sstream.open("../Debug/SaveFile.txt");
		for(int i = 0; i < 5; i++)
		{
			sstream << "unused_file_slot ";
			sstream << 1;
			sstream << " \n";
			mSLD[i].text = "unused_file_slot ";
			mSLD[i].mapID = 1;
		}
		sstream.close();
	}else
	{
		for(int i = 0; i < 5;i++)
		{
			stream >> mSLD[i].text;
			stream >> mSLD[i].mapID;
		}
	}
	if(mSLD[4].text == "")
		system("pause");
}


SaveLoad::~SaveLoad()
{
}

std::string SaveLoad::loadText(int slot)
{
	return  mSLD[slot].text;
}


void SaveLoad::save(int activeSlot, std::string name, int mapID)
{
	if(activeSlot >= 0 && activeSlot <= 4 && mapID >= 1)
	{
		mSLD[activeSlot].text = name;
		mSLD[activeSlot].mapID = mapID;
		std::ofstream stream;
		stream.open("../Debug/SaveFile.txt");
		for(int i = 0; i < 5;i++)
		{
			stream << mSLD[i].text;
			stream << " ";
			stream << mSLD[i].mapID;
			stream << " \n";
		}
		stream.close();
	}
}

int SaveLoad::load(int activeSlot)const
{
	if(activeSlot >= 0 && activeSlot <= 4)
		return mSLD[activeSlot].mapID;
}