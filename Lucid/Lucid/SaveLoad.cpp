#include "SaveLoad.h"


SaveLoad::SaveLoad()
{
	std::fstream stream("../Debug/SaveFile.txt");
	if(!stream.is_open())
	{
		std::ofstream sstream;
		sstream.open("../Debug/SaveFile.txt");
		for(int i = 0; i < 5; i++)
		{
			sstream << "unused_file_slot ";
			sstream << 0;
			sstream << " \n";
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
}


SaveLoad::~SaveLoad()
{
}
