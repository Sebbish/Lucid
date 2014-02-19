#ifndef AMBIANCE_H
#define AMBIANCE_H
#include "SFML/Audio.hpp"
#include <iostream>
class ambiance
{
public:
	ambiance();
	~ambiance();
	void tick();
private:
	int ambMaxVolume;
	int ambMadness;

	// VARIABLES AA //
	int ambAAVolume;
	int ambAADynamics;
	int ambAARandom;
	int ambAALength;
	float ambAAPitch;
	int ambAASecCounter;
	bool ambAAFadeOut;
	int ambAAFadeSpeed;
	float ambAAIntToFloat;

	// VARIABLES AB //
	int ambABVolume;
	int ambABDynamics;
	int ambABRandom;
	int ambABLength;
	float ambABPitch;
	int ambABSecCounter;
	bool ambABFadeOut;
	int ambABFadeSpeed;
	float ambABIntToFloat;

	// VARIABLES BA //
	int ambBAVolume;
	int ambBADynamics;
	int ambBARandom;
	int ambBALength;
	float ambBAPitch;
	int ambBASecCounter;
	bool ambBAFadeOut;
	int ambBAFadeSpeed;
	float ambBAIntToFloat;

	// VARIABLES BB //
	int ambBBVolume;
	int ambBBDynamics;
	int ambBBRandom;
	int ambBBLength;
	float ambBBPitch;
	int ambBBSecCounter;
	bool ambBBFadeOut;
	int ambBBFadeSpeed;
	float ambBBIntToFloat;

	int frameCounter;

	sf::Music ambAA,ambAB,ambBA,ambBB;
};
#endif
