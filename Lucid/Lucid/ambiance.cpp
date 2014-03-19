#include "ambiance.h"

using namespace std;

// FILE PATH //
//string path = "P:/Downloads/LucidProject/Resources/Sound/Ambiance/";
string path = "../../../LucidProject/Resources/Sound/Ambiance/";

	// VARIABLES A //
	int ambAAFrameCounter = 0;
	int ambAAVolume = 0;
	int ambAADynamics = 0;
	int ambAARandom = 0;
	int ambAALength = 0;
	float ambAAPitch = 0;
	int ambAASecCounter = 0;
	bool ambAAFadeOut = false;
	int ambAAFadeSpeed = 0;
	float ambAAIntToFloat = 0;

	int ambABFrameCounter = 0;
	int ambABVolume = 0;
	int ambABDynamics = 0;
	int ambABRandom = 0;
	int ambABLength = 0;
	float ambABPitch = 0;
	int ambABSecCounter = 0;
	bool ambABFadeOut = false;
	int ambABFadeSpeed = 0;
	float ambABIntToFloat = 0;

	// VARIABLES B //
	int ambBARandom = 0;
	int ambBAVolume = 0;
	bool ambBAUpDown = 0;
	bool ambBAOffOn = 0;
	int ambBAFrameCounter = 0;
	int ambBAFadeInSpeed = 0;
	int ambBAFadeOutSpeed = 0;
	float ambBAPitch = 0;
	float ambBAIntToFloat = 0;
	int ambBATriggerLevel = 40;

	int ambBBRandom = 0;
	int ambBBVolume = 0;
	bool ambBBUpDown = 0;
	bool ambBBOffOn = 0;
	int ambBBFrameCounter = 0;
	int ambBBFadeInSpeed = 0;
	int ambBBFadeOutSpeed = 0;
	float ambBBPitch = 0;
	float ambBBIntToFloat = 0;
	int ambBBTriggerLevel = 50;

	int ambBCRandom = 0;
	int ambBCVolume = 0;
	bool ambBCUpDown = 0;
	bool ambBCOffOn = 0;
	int ambBCFrameCounter = 0;
	int ambBCFadeInSpeed = 0;
	int ambBCFadeOutSpeed = 0;
	float ambBCPitch = 0;
	float ambBCIntToFloat = 0;
	int ambBCTriggerLevel = 60;

	// VARIABLES C //
	int ambCATriggerLevel = 75;
	int ambCARandom = 0;
	float ambCAPitch = 0;

	int ambCBTriggerLevel = 85;
	int ambCBRandom = 0;
	float ambCBPitch = 0;

	int ambCCTriggerLevel = 95;
	int ambCCRandom = 0;
	float ambCCPitch = 0;

	// VARIABLES D //
	int ambDCounter = 0;
	bool ambDBeforeAfter = 0;
	int ambDTriggerLevel = 90;
	int ambDTimer = 0;

	// FILE LIST A //
	string ambAAFile[10] = {
	"ambAA01.ogg", "ambAA02.ogg", "ambAA03.ogg", "ambAA04.ogg", "ambAA05.ogg",
	"ambAA06.ogg", "ambAA07.ogg", "ambAA08.ogg", "ambAA09.ogg", "ambAA10.ogg"
	};

	string ambABFile[10] = {
	"ambAB01.ogg", "ambAB02.ogg", "ambAB03.ogg", "ambAB04.ogg", "ambAB05.ogg",
	"ambAB06.ogg", "ambAB07.ogg", "ambAB08.ogg", "ambAB09.ogg", "ambAB10.ogg",
	};

	// FILE LIST B //
	string ambBAFile[2] = {
	"ambBA01.ogg", "ambBA02.ogg"
	};

	string ambBBFile[2] = {
	"ambBA01.ogg", "ambBA02.ogg"
	};

	string ambBCFile[2] = {
	"ambBA01.ogg", "ambBA02.ogg"
	};

	// FILE LIST C //
	string ambCAFile[2] = {
	"ambCA01.ogg", "ambCA02.ogg"
	};

	string ambCBFile[2] = {
	"ambCB01.ogg", "ambCB02.ogg"
	};

	string ambCCFile[2] = {
	"ambCC01.ogg", "ambCC02.ogg"
	};

	// VOLUME TABLES //
	int ambDCVolumeTable[12] = {
	80, 70, 60, 50, 40, 30,
	20, 10, 5, 3, 2, 1
	};

	int ambDDVolumeTable[12] = {
	3, 5, 7, 10, 13, 15,
	17, 20, 15, 10, 7, 5
	};

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

	sf::Music ALLambAA[10];
	sf::Music ALLambAB[10];

	sf::Music ALLambBA[2];
	sf::Music ALLambBB[2];
	sf::Music ALLambBC[2];

	sf::Music ALLambCA[2];
	sf::Music ALLambCB[2];
	sf::Music ALLambCC[2];

	sf::Music ambDD;
	sf::Music ambDC;
	sf::Music ambDB;
	sf::Music ambDA;

ambiance::ambiance()
{
// INSTANCES D //

	ambDA.setVolume(0);
	ambDA.setLoop(false); 

	ambDB.setVolume(100);
	ambDB.setLoop(false); 

	ambDC.setVolume(100);
	ambDC.setLoop(false);

	ambDD.setVolume(100);
	ambDD.setLoop(false);

	ambDA.openFromFile("ambDA01.ogg");
	ambDB.openFromFile("ambDB01.ogg");
	ambDC.openFromFile("ambDC01.ogg");
	ambDD.openFromFile("ambDD01.ogg");

	// LOAD ALL FILES (AKA RONNYHAX) ////////////////////////////////////////////


	for(int i = 0; i < ARRAY_SIZE(ambAAFile); i++)
	{
		ALLambAA[i].openFromFile(path+ambAAFile[i]);
		ALLambAA[i].setVolume(0);
		ALLambAA[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambABFile); i++)
	{
		ALLambAB[i].openFromFile(path+ambABFile[i]);
		ALLambAB[i].setVolume(0);
		ALLambAB[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambBAFile); i++)
	{
		ALLambBA[i].openFromFile(path+ambBAFile[i]);
		ALLambBA[i].setVolume(0);
		ALLambBA[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambBBFile); i++)
	{
		ALLambBB[i].openFromFile(path+ambBBFile[i]);
		ALLambBB[i].setVolume(0);
		ALLambBB[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambBCFile); i++)
	{
		ALLambBC[i].openFromFile(path+ambBCFile[i]);
		ALLambBC[i].setVolume(0);
		ALLambBC[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambCAFile); i++)
	{
		ALLambCA[i].openFromFile(path+ambCAFile[i]);
		ALLambCA[i].setVolume(0);
		ALLambCA[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambCBFile); i++)
	{
		ALLambCB[i].openFromFile(path+ambCBFile[i]);
		ALLambCB[i].setVolume(0);
		ALLambCB[i].setLoop(true); 
	}

	for(int i = 0; i < ARRAY_SIZE(ambCCFile); i++)
	{
		ALLambCC[i].openFromFile(path+ambCCFile[i]);
		ALLambCC[i].setVolume(0);
		ALLambCC[i].setLoop(true); 
	}
	// RAND TIME & ARRAYLENGTH DEFINITION //
		srand (time(0));	
}

ambiance::~ambiance()
{
}

void ambiance::tick(int madness)
{
	ambMadness = 100-madness;
	ambMaxVolume = 100;

	// SO THE ENGINE BEGINS //

		// IF NOT PLAYING AA ///////////////////////////////////////////////////
		
		if (ALLambAA[ambAARandom].getStatus() == 0)
		{
			// FILE SELECTOR //
			ambAARandom = rand()% ARRAY_SIZE(ambAAFile);
			//ALLambAA[ambAARandom].openFromFile(ambAAFile[ambAARandom]);

			// VOLUME RESET //
			ALLambAA[ambAARandom].setVolume(0);
			ambAAVolume = 0;
			ambAADynamics = 100000;

			// LENGTH //
			ambAALength = rand() % 60 + 40;
			ambAASecCounter = 0;

			// FADE //
			ambAAFadeSpeed = rand()% 2 + 3;
			ambAAFadeOut = false;

			// PITCH //
			ambAAPitch = rand() % 100;
			ambAAPitch = ambAAPitch/200+0.75;
			ALLambAA[ambAARandom].setPitch(ambAAPitch);
				
			// PLAY //
			ALLambAA[ambAARandom].play();
		}

		// IF NOT PLAYING AB /////////////////////////////////////////////////////////

		if (ALLambAB[ambABRandom].getStatus() == 0)
		{
			// FILE SELECTOR //
			ambABRandom = rand()% ARRAY_SIZE(ambABFile);
			//ALLambAB[ambABRandom].openFromFile(ambABFile[ambABRandom]);

			// VOLUME RESET //
			ALLambAB[ambABRandom].setVolume(0);
			ambABVolume = 0;
			ambABDynamics = 100000;

			// LENGTH //
			ambABLength = rand() % 30 + 30;
			ambABSecCounter = 0;

			// FADE //
			ambABFadeSpeed = rand()% 2 + 3;
			ambABFadeOut = false;

			// PITCH //
			ambABPitch = rand() % 100;
			ambABPitch = ambABPitch/200+0.75;
			ALLambAB[ambABRandom].setPitch(ambABPitch);
				
			// PLAY //
			ALLambAB[ambABRandom].play();
		}
		
		// FADE AA ////////////////////////////////////////////////////////////////
		
		// COUNTERS //

		ambAAFrameCounter++;

		if (ambAAFrameCounter>60)
		{
			ambAAFrameCounter = 0;
			ambAASecCounter++;
		}

		// FADE //

		if (ALLambAB[ambABRandom].getStatus() == 2)
		{
			ambAADynamics = 10000*(ambMadness*0.25/100) + 2500;

			// FADE VOLUME UP //

			if (ambAAVolume + ambAAFadeSpeed < ambAADynamics && ambAAFadeOut == false)
			{
				ambAAVolume = ambAAVolume + ambAAFadeSpeed;

				ambAAIntToFloat = ambAAVolume;
				ALLambAA[ambAARandom].setVolume(ambAAIntToFloat/100*(ambMaxVolume/100));
			}

			// FADE VOLUME DOWN //

			else if (ambAAVolume > ambAADynamics && ambAAFadeOut == false)
			{
				ambAAVolume = ambAAVolume - ambAAFadeSpeed*2;

				ambAAIntToFloat = ambAAVolume;
				ALLambAA[ambAARandom].setVolume(ambAAIntToFloat/100*(ambMaxVolume/100));
			}

			// FADE OUT //

			if (ambAASecCounter > ambAALength && ambABFadeOut == false)
			{
				ambAAFadeOut = true;

				if (ambAAVolume > ambAAFadeSpeed)
				{
					ambAAVolume = ambAAVolume - ambAAFadeSpeed;

					ambAAIntToFloat = ambAAVolume;
					ALLambAA[ambAARandom].setVolume(ambAAIntToFloat/100*(ambMaxVolume/100));
				}

				// STOP //

				if (ambAAVolume <= ambAAFadeSpeed*2)
				{
					ambAAVolume = 0;
					ambAAFadeOut = false;
					ALLambAA[ambAARandom].setVolume(0);
					ALLambAA[ambAARandom].stop();
				}
			}
		}

		// FADE AB ////////////////////////////////////////////////////////////////
		
		// COUNTERS //

		ambABFrameCounter++;

		if (ambABFrameCounter>60)
		{
			ambABFrameCounter = 0;
			ambABSecCounter++;
		}

		// FADE //

		if (ALLambAB[ambABRandom].getStatus() == 2)
		{
			ambABDynamics = 10000*(ambMadness*0.4/100) + 1000;

			// FADE VOLUME UP //

			if (ambABVolume + ambABFadeSpeed < ambABDynamics && ambABFadeOut == false)
			{
				ambABVolume = ambABVolume + ambABFadeSpeed;

				ambABIntToFloat = ambABVolume;
				ALLambAB[ambABRandom].setVolume(ambABIntToFloat/100*(ambMaxVolume/100));
			}

			// FADE VOLUME DOWN //

			else if (ambABVolume > ambABDynamics && ambABFadeOut == false)
			{
				ambABVolume = ambABVolume - ambABFadeSpeed*2;

				ambABIntToFloat = ambABVolume;
				ALLambAB[ambABRandom].setVolume(ambABIntToFloat/100*(ambMaxVolume/100));
			}

			// FADE OUT //

			if (ambABSecCounter > ambABLength && ambAAFadeOut == false)
			{
				ambABFadeOut = true;

				if (ambABVolume > ambABFadeSpeed)
				{
					ambABVolume = ambABVolume - ambABFadeSpeed;

					ambABIntToFloat = ambABVolume;
					ALLambAB[ambABRandom].setVolume(ambABIntToFloat/100*(ambMaxVolume/100));
				}

				// STOP //

				if (ambABVolume <= ambABFadeSpeed*2)
				{
					ambABVolume = 0;
					ambABFadeOut = false;
					ALLambAB[ambABRandom].setVolume(0);
					ALLambAB[ambABRandom].stop();
				}
			}
		}

		// IF NOT PLAYING BA /////////////////////////////////////////////////////////
		
		if (ALLambBA[ambBARandom].getStatus() == 0 && ambMadness > ambBATriggerLevel)
		{
			// FILE SELECTOR //
			ambBARandom = rand()% ARRAY_SIZE(ambBAFile);
			//ALLambBA[ambBARandom].openFromFile(ambBAFile[ambBARandom]);

			// RESETS //
			ALLambBA[ambBARandom].setVolume(0);
			ambBAUpDown = 0;
			ambBAOffOn = 0;

			// PLAY //
			ALLambBA[ambBARandom].play();
		}

		// IF NOT PLAYING BB /////////////////////////////////////////////////////////
		
		if (ALLambBB[ambBBRandom].getStatus() == 0 && ambMadness > ambBBTriggerLevel)
		{
			// FILE SELECTOR //
			ambBBRandom = rand()% ARRAY_SIZE(ambBBFile);
			//ALLambBB[ambBBRandom].openFromFile(ambBBFile[ambBBRandom]);

			// RESETS //
			ALLambBB[ambBBRandom].setVolume(0);
			ambBBUpDown = 0;
			ambBBOffOn = 0;

			// PLAY //
			ALLambBB[ambBBRandom].play();
		}

		// IF NOT PLAYING BC /////////////////////////////////////////////////////////
		
		if (ALLambBC[ambBCRandom].getStatus() == 0 && ambMadness > ambBCTriggerLevel)
		{
			// FILE SELECTOR //
			ambBCRandom = rand()% ARRAY_SIZE(ambBCFile);
			//ALLambBC[ambBCRandom].openFromFile(ambBCFile[ambBCRandom]);

			// RESETS //
			ALLambBC[ambBCRandom].setVolume(0);
			ambBCUpDown = 0;
			ambBCOffOn = 0;

			// PLAY //
			ALLambBC[ambBCRandom].play();
		}
		
		// FADE BA ////////////////////////////////////////////////////////////////
		
		if (ALLambBA[ambBARandom].getStatus() == 2)
		{
			// TRIGGER //

			ambBAFrameCounter++;

			if (ambBAOffOn == 0 && ambBAFrameCounter-300 + (ambMadness-ambBATriggerLevel)*7 + rand()% 200 > 500)
			{
				ambBAOffOn = 1;

				ambBAFadeInSpeed = 300 + (ambMadness-ambBATriggerLevel)*5 + rand()% 200;
				ambBAFadeOutSpeed = 20 + (ambMadness-ambBATriggerLevel)/2 + rand()% 30;

				ambBAPitch = rand() % 100;
				ambBAPitch = ambBAPitch/200+0.75;
				ALLambBA[ambBARandom].setPitch(ambBAPitch*(ambMadness/200)+0.5);
			}

			// FADE IN //

			if (ambBAOffOn == 1 && ambBAUpDown == 0)
			{
				ambBAVolume = ambBAVolume + ambBAFadeInSpeed;

				ambBAIntToFloat = ambBAVolume;
				ambBAIntToFloat = ambBAIntToFloat/100;
				ALLambBA[ambBARandom].setVolume(100*(ambBAIntToFloat*ambBAIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBAVolume > 10000)
				{
					ambBAUpDown = 1;
				}
			}

			// FADE OUT //

			else if (ambBAUpDown == 1)
			{
				ambBAVolume = ambBAVolume - ambBAFadeOutSpeed;

				ambBAIntToFloat = ambBAVolume;
				ambBAIntToFloat = ambBAIntToFloat/100;
				ALLambBA[ambBARandom].setVolume(100*(ambBAIntToFloat*ambBAIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBAVolume <= ambBAFadeOutSpeed*2)
				{
					ambBAUpDown = 0;
					ambBAOffOn = 0;
					ambBAFrameCounter = 0;
					ambBAVolume = 0;
					ambBAIntToFloat = 0;
					ALLambBA[ambBARandom].setVolume(0);
				}
			}

			// STOP //

			if (ambMadness < ambBATriggerLevel && ALLambBA[ambBARandom].getVolume() == 0)
			{
				ambBAUpDown = 0;
				ambBAOffOn = 0;
				ambBAFrameCounter = 0;
				ambBAVolume = 0;
				ambBAIntToFloat = 0;
				ALLambBA[ambBARandom].setVolume(0);
				ALLambBA[ambBARandom].stop();
			}
		}

		// FADE BB ////////////////////////////////////////////////////////////////
		
		if (ALLambBB[ambBBRandom].getStatus() == 2)
		{
			// TRIGGER //

			ambBBFrameCounter++;

			if (ambBBOffOn == 0 && ambBBFrameCounter-200 + (ambMadness-ambBBTriggerLevel)*7 + rand()% 200 > 400)
			{
				ambBBOffOn = 1;

				ambBBFadeInSpeed = 300 + (ambMadness-ambBBTriggerLevel)*5 + rand()% 200;
				ambBBFadeOutSpeed = 20 + (ambMadness-ambBBTriggerLevel)/2 + rand()% 30;

				ambBBPitch = rand() % 100;
				ambBBPitch = ambBBPitch/200+0.75;
				ALLambBB[ambBBRandom].setPitch(ambBBPitch*(ambMadness/200)+0.5);
			}

			// FADE IN //

			if (ambBBOffOn == 1 && ambBBUpDown == 0)
			{
				ambBBVolume = ambBBVolume + ambBBFadeInSpeed;

				ambBBIntToFloat = ambBBVolume;
				ambBBIntToFloat = ambBBIntToFloat/100;
				ALLambBB[ambBBRandom].setVolume(100*(ambBBIntToFloat*ambBBIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBBVolume > 10000)
				{
					ambBBUpDown = 1;
				}
			}

			// FADE OUT //

			else if (ambBBUpDown == 1)
			{
				ambBBVolume = ambBBVolume - ambBBFadeOutSpeed;

				ambBBIntToFloat = ambBBVolume;
				ambBBIntToFloat = ambBBIntToFloat/100;
				ALLambBB[ambBBRandom].setVolume(100*(ambBBIntToFloat*ambBBIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBBVolume <= ambBBFadeOutSpeed*2)
				{
					ambBBUpDown = 0;
					ambBBOffOn = 0;
					ambBBFrameCounter = 0;
					ambBBVolume = 0;
					ambBBIntToFloat = 0;
					ALLambBB[ambBBRandom].setVolume(0); 
				}
			}

			// STOP //

			if (ambMadness < ambBBTriggerLevel && ALLambBB[ambBBRandom].getVolume() == 0)
			{
				ambBBUpDown = 0;
				ambBBOffOn = 0;
				ambBBFrameCounter = 0;
				ambBBVolume = 0;
				ambBBIntToFloat = 0;
				ALLambBB[ambBBRandom].setVolume(0);
				ALLambBB[ambBBRandom].stop();
			}
		}

		// FADE BC ////////////////////////////////////////////////////////////////
		
		if (ALLambBC[ambBCRandom].getStatus() == 2)
		{
			// TRIGGER //

			ambBCFrameCounter++;

			if (ambBCOffOn == 0 && ambBCFrameCounter-100 + (ambMadness-ambBCTriggerLevel)*7 + rand()% 200 > 300)
			{
				ambBCOffOn = 1;

				ambBCFadeInSpeed = 300 + (ambMadness-ambBCTriggerLevel)*5 + rand()% 200;
				ambBCFadeOutSpeed = 20 + (ambMadness-ambBCTriggerLevel)/2 + rand()% 30;

				ambBCPitch = rand() % 100;
				ambBCPitch = ambBCPitch/200+0.75;
				ALLambBC[ambBCRandom].setPitch(ambBCPitch*(ambMadness/200)+0.5);
			}

			// FADE IN //

			if (ambBCOffOn == 1 && ambBCUpDown == 0)
			{
				ambBCVolume = ambBCVolume + ambBCFadeInSpeed;

				ambBCIntToFloat = ambBCVolume;
				ambBCIntToFloat = ambBCIntToFloat/100;
				ALLambBC[ambBCRandom].setVolume(100*(ambBCIntToFloat*ambBCIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBCVolume > 10000)
				{
					ambBCUpDown = 1;
				}
			}

			// FADE OUT //

			else if (ambBCUpDown == 1)
			{
				ambBCVolume = ambBCVolume - ambBCFadeOutSpeed;

				ambBCIntToFloat = ambBCVolume;
				ambBCIntToFloat = ambBCIntToFloat/100;
				ALLambBC[ambBCRandom].setVolume(100*(ambBCIntToFloat*ambBCIntToFloat/100*((ambMadness-40)/100)/100)*(ambMaxVolume/100));

				if (ambBCVolume <= ambBCFadeOutSpeed*2)
				{
					ambBCUpDown = 0;
					ambBCOffOn = 0;
					ambBCFrameCounter = 0;
					ambBCVolume = 0;
					ambBCIntToFloat = 0;
					ALLambBC[ambBCRandom].setVolume(0);
				}
			}

			// STOP //

			if (ambMadness < ambBCTriggerLevel && ALLambBC[ambBCRandom].getVolume() == 0)
			{
				ambBCUpDown = 0;
				ambBCOffOn = 0;
				ambBCFrameCounter = 0;
				ambBCVolume = 0;
				ambBCIntToFloat = 0;
				ALLambBC[ambBCRandom].setVolume(0);
				ALLambBC[ambBCRandom].stop();
			}
		}

		// IF NOT PLAYING CA /////////////////////////////////////////////////////////
		
		if (ambMadness > ambCATriggerLevel && ALLambCA[ambCARandom].getStatus() == 0)
		{
			// FILE SELECTOR //
			ambCARandom = rand()% ARRAY_SIZE(ambCAFile);
			//ALLambCA[ambCARandom].openFromFile(ambCAFile[ambCARandom]);

			// VOLUME RESET //
			ALLambCA[ambCARandom].setVolume(0);

			// PITCH //
			ambCAPitch = rand() % 100;
			ambCAPitch = ambCAPitch/400+0.87;
			ALLambCA[ambCARandom].setPitch(ambCAPitch);
				
			// PLAY //
			ALLambCA[ambCARandom].play();
		}

		// IF NOT PLAYING CB /////////////////////////////////////////////////////////

		if ( ambMadness > ambCBTriggerLevel && ALLambCB[ambCBRandom].getStatus() == 0)
		{
			// FILE SELECTOR //
			ambCBRandom = rand()% ARRAY_SIZE(ambCBFile);
			//ALLambCB[ambCBRandom].openFromFile(ambCBFile[ambCBRandom]);

			// VOLUME RESET //
			ALLambCB[ambCBRandom].setVolume(0);

			// PITCH //
			ambCBPitch = rand() % 100;
			ambCBPitch = ambCBPitch/400+0.87;
			ALLambCB[ambCBRandom].setPitch(ambCBPitch);
				
			// PLAY //
			ALLambCB[ambCBRandom].play();
		}

		// IF NOT PLAYING CC /////////////////////////////////////////////////////////

		if (ambMadness > ambCCTriggerLevel && ALLambCC[ambCCRandom].getStatus() == 0)
		{
			// FILE SELECTOR //
			ambCCRandom = rand()% ARRAY_SIZE(ambCCFile);
			//ALLambCC[ambCCRandom].openFromFile(ambCCFile[ambCCRandom]);

			// VOLUME RESET //
			ALLambCC[ambCCRandom].setVolume(0);

			// PITCH //
			ambCCPitch = rand() % 100;
			ambCCPitch = ambCCPitch/400+0.87;
			ALLambCC[ambCCRandom].setPitch(ambCCPitch);
				
			// PLAY //
			ALLambCC[ambCCRandom].play();
		}
		
		// VOLUME CA ////////////////////////////////////////////////////////////////

		if (ALLambCA[ambCARandom].getStatus() == 2)
		{
			ALLambCA[ambCARandom].setVolume((ambMadness - ambCATriggerLevel)*(ambMadness/100+1)*0.50*(ambMaxVolume/100)*0.75);

			// STOP //

			if (ambMadness <= ambCATriggerLevel)
			{
				ALLambCA[ambCARandom].stop();
				ALLambCA[ambCARandom].setVolume(0);
			}
		}

		// VOLUME CB ////////////////////////////////////////////////////////////////

		if (ALLambCB[ambCBRandom].getStatus() == 2)
		{
			ALLambCB[ambCBRandom].setVolume((ambMadness - ambCBTriggerLevel)*(ambMadness/100+1)*0.75*(ambMaxVolume/100)*0.75);

			// STOP //

			if (ambMadness <= ambCBTriggerLevel)
			{
				ALLambCB[ambCBRandom].stop();
				ALLambCB[ambCBRandom].setVolume(0);
			}
		}

		// VOLUME CC ////////////////////////////////////////////////////////////////

		if (ALLambCC[ambCCRandom].getStatus() == 2)
		{
			ALLambCC[ambCCRandom].setVolume((ambMadness - ambCCTriggerLevel)*(ambMadness/100+1)*2*(ambMaxVolume/100)*0.75);

			// STOP //

			if (ambMadness <= ambCCTriggerLevel)
			{
				ALLambCC[ambCCRandom].stop();
				ALLambCC[ambCCRandom].setVolume(0);
			}
		}
		
		// PLAY D //////////////////////////////////////////////////////////////////////////////
		
		if (ambMadness > ambDTriggerLevel || ambDBeforeAfter == 1)
		{
			ambDCounter++;
			
			// LONG BEEP TRIGGER //

			if (ambMadness >= 100 && ambDB.getStatus() == 0)
			{
				ambDA.stop();
				ambDB.setVolume(ambMaxVolume*0.60);
				ambDB.play();
				ambDBeforeAfter = 1;
				ambDTimer = 0;
			}
			
			// BEFORE BEEP PLAY //

			else if (ambDCounter > 160-((ambMadness*ambMadness)/75) && ambDBeforeAfter == 0 && ambDB.getStatus() == 0)
			{
				ambDCounter = 0;

				ambDA.setVolume((ambMadness-ambDTriggerLevel)*(ambMadness-ambDTriggerLevel)*(ambMaxVolume/100)*0.60);
				ambDA.play();
			}
			
			// AFTER BEEP PLAY //

			else if (ambDB.getStatus() == 0 && ambDCounter > 90 && ambDBeforeAfter == 1)
			{
				ambDCounter = 0;
				ambDTimer++;

				ambDC.setVolume(ambDCVolumeTable[ambDTimer]*(ambMaxVolume/100)*0.4);
				ambDD.setVolume(ambDDVolumeTable[ambDTimer]*(ambMaxVolume/100)*0.4);

				if (ambDBeforeAfter == 1)
				{
					ambDC.play();
					ambDD.play();
				}

				// STOP //

				if (ambDTimer == 11)
				{
					ambDBeforeAfter = 0;
					ambDTimer = 0;
				}
			}
		}
	}