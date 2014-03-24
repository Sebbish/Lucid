#ifndef AMBIANCE_H
#define AMBIANCE_H
#include "SFML/Audio.hpp"
#include <iostream>
class ambiance
{
public:
	ambiance();
	~ambiance();
	void tick(int madness);
private:
	float ambMaxVolume;
	int ambMadness;
};
#endif
