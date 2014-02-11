#include <iostream>
#include <string>
#include <time.h>
#include "SFML/Audio.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// MAIN /////////////////////////////////////////////////////////////////////////////////

int maina()
{
	sf::Window window(sf::VideoMode(10, 10), "Mackan Plz"); // <------------------- REMOVE
	window.setFramerateLimit(60); // <-------------------------------------------- REMOVE
	//window.setVerticalSyncEnabled(true);

	int frameCounter = 0; // <----------------------------------------------------- LINK TO THE GAME? :)
	int ambMaxVolume = 100; // <--------------------------------------------------- LINK TO THE GAME
	int ambMadness = 100; // <----------------------------------------------------- LINK TO THE GAME
	
	// VARIABLES A //

	float ambAVolume = 0;
	float ambADynamics = 0;
	int ambARandom = 0;
	int ambALength = 0;
	float ambAPitch = 0;
	int ambASecCounter = 0;
	bool ambAFadeIn = false;
	bool ambAFadeOut = false;
	float ambAFadeSpeed = 0;

	// VARIABLES B //

	float ambBVolume = 0;
	float ambBDynamics = 0;
	int ambBRandom = 0;
	int ambBLength = 0;
	float ambBPitch = 0;
	int ambBSecCounter = 0;
	bool ambBFadeIn = false;
	bool ambBFadeOut = false;
	float ambBFadeSpeed = 0;

	// FILE LIST //

	string ambFile[16] = { //OGG SUPPORT C:
	"amb00.wav", "amb01.wav", "amb02.wav", "amb03.wav", "amb04.wav",
	"amb05.wav", "amb06.wav", "amb07.wav", "amb08.wav", "amb09.wav",
	"amb10.wav", "amb11.wav", "amb12.wav", "amb13.wav", "amb14.wav",
	"amb15.wav"//, "amb16.wav", "amb17.wav", "amb18.wav", "amb19.wav",
	//"amb20.wav", "amb21.wav", "amb22.wav", "amb23.wav", "amb24.wav",
	//"amb25.wav", "amb26.wav", "amb27.wav", "amb28.wav", "amb29.wav"
	};

	// MUSIC INSTANCE A //

	sf::Music ambA;
	ambA.setVolume(0);
	ambA.setLoop(true); 

	// MUSIC INSTANCE B //

	sf::Music ambB;
	ambB.setVolume(0);
	ambB.setLoop(true); 

	// RAND TIME & ARRAYLENGTH DEFINITION //

	srand (time(0));
	#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

	// AMBIENCELOOP ////////////////////////////////////////////////////////////////////

	while(true)
	{
		window.display(); // <---------------------------------------------------- REMOVE
		frameCounter++; // <------------------------------------------------------ LINK TO THE GAME? :)

		// TEST SECTION // // <--------------------------------------------------- REMOVE

		cout << "Madness is " << ambMadness << endl;

		//cout << "ambAVolume is now " << ambAVolume << endl;
		//cout << "ambADynamics is " << ambADynamics << endl;
		//cout << "the ambAfadespeed is now " << ambAFadeSpeed << endl;
		//cout << "ambApitch is now " << ambA.getPitch() << endl;
		//cout << "ambASecACounter is " << ambASecCounter << endl;
		//cout << "ambALength is " << ambALength << endl;
		cout << "ambA getVolume is " << ambA.getVolume() << endl;

		//cout << "ambBVolume is now " << ambBVolume << endl;
		//cout << "ambBDynamics is " << ambBDynamics << endl;
		//cout << "the ambBfadespeed is now " << ambBFadeSpeed << endl;
		//cout << "ambBpitch is now " << ambB.getPitch() << endl;
		//cout << "ambBSecACounter is " << ambBSecCounter << endl;
		//cout << "ambBLength is " << ambBLength << endl;
		cout << "ambB getVolume is " << ambB.getVolume() << endl;

		// VOLUME ////////////////////////////////////////////////////////////////////

		// VOLUME A //

		ambA.setVolume(ambAVolume*(ambMaxVolume/100));

		// VOLUME B //

		ambB.setVolume(ambBVolume*(ambMaxVolume/100));

		// DYNAMICS //////////////////////////////////////////////////////////////////

		// DYNAMICS A //

		ambADynamics = (ambMadness*0.75) + 25;

		// DYNAMICS B //

		ambBDynamics = (ambMadness*0.75) + 25;

		// FADE IN ///////////////////////////////////////////////////////////////////

		// FADE IN A //

		if (ambAFadeIn == true)
		{
			if (ambAVolume < ambADynamics)
			{
				ambAVolume = ambAVolume + ambAFadeSpeed;
			}

			else if (ambAVolume > ambADynamics)
			{
				ambAVolume = ambAVolume - ambAFadeSpeed;
			}

			else if (ambAVolume == ambADynamics)
			{
				ambAFadeIn = false;
			}
		}

		// FADE IN B //

		if (ambBFadeIn == true)
		{
			if (ambBVolume < ambBDynamics)
			{
				ambBVolume = ambBVolume + ambBFadeSpeed;
			}

			else if (ambBVolume > ambBDynamics)
			{
				ambBVolume = ambBVolume - ambBFadeSpeed;
			}

			else if (ambBVolume == ambBDynamics)
			{
				ambBFadeIn = false;
			}
		}

		// IF FADE OUT //////////////////////////////////////////////////////////////

		// IF FADE OUT A //

		if (ambAFadeOut == true)
		{
			if (ambAVolume > ambAFadeSpeed)
			{
				ambAVolume = ambAVolume - ambAFadeSpeed;
			}

			if (ambA.getVolume() < ambAFadeSpeed + ambAFadeSpeed)
			{
				ambAVolume = 0;
				ambAFadeIn = false;
				ambAFadeOut = false;
				ambASecCounter = 0;
				ambA.stop();
			}
		}

		// IF FADE OUT B //

		if (ambBFadeOut == true) // <<------------------------------------------------------- NOT THE SAME AS A!
		{
			if (ambBVolume > ambBFadeSpeed)
			{
				ambBVolume = ambBVolume - ambBFadeSpeed;
			}

			if (ambB.getVolume() < ambBFadeSpeed + ambBFadeSpeed)
			{
				ambBVolume = 0;
				ambBFadeIn = false;
				ambBFadeOut = false;
				ambBSecCounter = 0;
				ambB.stop();
			}
		}

		// COUNTERS //////////////////////////////////////////////////////////////////

		if (frameCounter>60)
		{
			frameCounter = 0;

			// COUNTER A //

			ambASecCounter++;

			// COUNTER B //

			ambBSecCounter++;

			// IF NOT PLAYING /////////////////////////////////////////////////////////

			// IF NOT PLAYING A //////////////////////////////////

			if (ambA.getStatus() == 0)
			{
				// FILE SELECTOR //
				ambARandom = rand() % ARRAY_SIZE(ambFile)*(ambMadness/100);
				ambA.openFromFile(ambFile[ambARandom]);

				// VOLUME RESET //
				ambA.setVolume(0);
				ambAVolume = 0;
				ambADynamics = 0;

				// LENGTH //
				ambALength = rand() % 15 + 15;
				ambASecCounter = 0;

				// FADE //
				ambAFadeSpeed = rand() % 5; 
				ambAFadeSpeed = ambAFadeSpeed / 60 + 0.01;
				ambAFadeIn = true;
				ambAFadeOut = false;

				// PITCH //
				ambAPitch = rand() % 50; 
				ambAPitch = ambAPitch / (ambMadness/2) + (ambMadness/200) + 0.5;
				ambA.setPitch(ambAPitch);

				// PLAY //
				ambA.play();
			}

			// IF NOT PLAYING B //////////////////////////////////

			if (ambB.getStatus() == 0)
			{
				// FILE SELECTOR //
				do {
				ambBRandom = rand() % ARRAY_SIZE(ambFile)*(ambMadness/100); //<<------------------- NOT THE SAME AS A!
				ambB.openFromFile(ambFile[ambBRandom]);
				} while (ambBRandom == ambARandom);

				// VOLUME RESET //
				ambB.setVolume(0);
				ambBVolume = 0;
				ambBDynamics = 0;

				// LENGTH //
				ambBLength = rand() % 15 + 15;
				ambBSecCounter = 0;

				// FADE //
				ambBFadeSpeed = rand() % 5; 
				ambBFadeSpeed = ambBFadeSpeed / 60 + 0.01;
				ambBFadeIn = true;
				ambBFadeOut = false;

				// PITCH //
				ambBPitch = rand() % 50; 
				ambBPitch = ambBPitch / (ambMadness/2) + (ambMadness/200) + 0.5;
				ambB.setPitch(ambBPitch);
				
				// PLAY //
				ambB.play();
			}


			// FADE OUT //////////////////////////////////////////////////////////////////

			// FADE OUT A //

			if (ambASecCounter > ambALength)
			{
				ambAFadeIn = false;
				ambAFadeOut = true;
			}

			// FADE OUT B //

			if (ambBSecCounter > ambBLength)
			{
				ambBFadeIn = false;
				ambBFadeOut = true;
			}
		}
	}
}