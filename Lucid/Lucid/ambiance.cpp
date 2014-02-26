#include "ambiance.h"

using namespace std;

// FILE PATH //
string path = "P:/Downloads/LucidProject/Resources/Sound/Ambiance/";


// FILE LIST AA //
	string ambAAFile[10] = {
	"ambAA01.ogg", "ambAA02.ogg", "ambAA03.ogg", "ambAA04.ogg", "ambAA05.ogg",
	"ambAA06.ogg", "ambAA07.ogg", "ambAA08.ogg", "ambAA09.ogg", "ambAA10.ogg",
	//"ambAA11.ogg", "ambAA12.ogg", "ambAA13.ogg", "ambAA14.ogg", "ambAA15.ogg",
	//"ambAA16.ogg", "ambAA17.ogg", "ambAA18.ogg", "ambAA19.ogg", "ambAA20.ogg",
	//"ambAA21.ogg", "ambAA22.ogg", "ambAA23.ogg", "ambAA24.ogg", "ambAA25.ogg",
	//"ambAA26.ogg", "ambAA27.ogg", "ambAA28.ogg", "ambAA29.ogg", "ambAA30.ogg",
	//"ambAA31.ogg", "ambAA32.ogg", "ambAA33.ogg", "ambAA34.ogg", "ambAA35.ogg",
	//"ambAA36.ogg", "ambAA37.ogg", "ambAA38.ogg", "ambAA39.ogg", "ambAA40.ogg",
	//"ambAA41.ogg", "ambAA42.ogg", "ambAA43.ogg", "ambAA44.ogg", "ambAA45.ogg",
	//"ambAA46.ogg", "ambAA47.ogg", "ambAA48.ogg", "ambAA49.ogg", "ambAA50.ogg"
	};

	// FILE LIST AB //
	string ambABFile[10] = {
	"ambAB01.ogg", "ambAB02.ogg", "ambAB03.ogg", "ambAB04.ogg", "ambAB05.ogg",
	"ambAB06.ogg", "ambAB07.ogg", "ambAB08.ogg", "ambAB09.ogg", "ambAB10.ogg",
	//"ambAB11.ogg", "ambAB12.ogg", "ambAB13.ogg", "ambAB14.ogg", "ambAB15.ogg",
	//"ambAB16.ogg", "ambAB17.ogg", "ambAB18.ogg", "ambAB19.ogg", "ambAB20.ogg",
	//"ambAB21.ogg", "ambAB22.ogg", "ambAB23.ogg", "ambAB24.ogg", "ambAB25.ogg",
	//"ambAB26.ogg", "ambAB27.ogg", "ambAB28.ogg", "ambAB29.ogg", "ambAB30.ogg",
	//"ambAB31.ogg", "ambAB32.ogg", "ambAB33.ogg", "ambAB34.ogg", "ambAB35.ogg",
	//"ambAB36.ogg", "ambAB37.ogg", "ambAB38.ogg", "ambAB39.ogg", "ambAB40.ogg",
	//"ambAB41.ogg", "ambAB42.ogg", "ambAB43.ogg", "ambAB44.ogg", "ambAB45.ogg",
	//"ambAB46.ogg", "ambAB47.ogg", "ambAB48.ogg", "ambAB49.ogg", "ambAB50.ogg"
	};

	// FILE LIST BA //
	string ambBAFile[7] = {
	"ambBA01.ogg", "ambBA02.ogg", "ambBA03.ogg", "ambBA04.ogg", "ambBA05.ogg",
	"ambBA06.ogg", "ambBA07.ogg",// "ambBA08.ogg", "ambBA09.ogg", "ambBA10.ogg",
	//"ambBA11.ogg", "ambBA12.ogg", "ambBA13.ogg", "ambBA14.ogg", "ambBA15.ogg",
	//"ambBA16.ogg", "ambBA17.ogg", "ambBA18.ogg", "ambBA19.ogg", "ambBA20.ogg",
	//"ambBA21.ogg", "ambBA22.ogg", "ambBA23.ogg", "ambBA24.ogg", "ambBA25.ogg",
	//"ambBA26.ogg", "ambBA27.ogg", "ambBA28.ogg", "ambBA29.ogg", "ambBA30.ogg",
	//"ambBA31.ogg", "ambBA32.ogg", "ambBA33.ogg", "ambBA34.ogg", "ambBA35.ogg",
	//"ambBA36.ogg", "ambBA37.ogg", "ambBA38.ogg", "ambBA39.ogg", "ambBA40.ogg",
	//"ambBA41.ogg", "ambBA42.ogg", "ambBA43.ogg", "ambBA44.ogg", "ambBA45.ogg",
	//"ambBA46.ogg", "ambBA47.ogg", "ambBA48.ogg", "ambBA49.ogg", "ambBA50.ogg"
	};

	// FILE LIST BA //
	string ambBBFile[9] = {
	"ambBB01.ogg", "ambBB02.ogg", "ambBB03.ogg", "ambBB04.ogg", "ambBB05.ogg",
	"ambBB06.ogg", "ambBB07.ogg", "ambBB08.ogg", "ambBB09.ogg",// "ambBB10.ogg",
	//"ambBB11.ogg", "ambBB12.ogg", "ambBB13.ogg", "ambBB14.ogg", "ambBB15.ogg",
	//"ambBB16.ogg", "ambBB17.ogg", "ambBB18.ogg", "ambBB19.ogg", "ambBB20.ogg",
	//"ambBB21.ogg", "ambBB22.ogg", "ambBB23.ogg", "ambBB24.ogg", "ambBB25.ogg",
	//"ambBB26.ogg", "ambBB27.ogg", "ambBB28.ogg", "ambBB29.ogg", "ambBB30.ogg",
	//"ambBB31.ogg", "ambBB32.ogg", "ambBB33.ogg", "ambBB34.ogg", "ambBB35.ogg",
	//"ambBB36.ogg", "ambBB37.ogg", "ambBB38.ogg", "ambBB39.ogg", "ambBB40.ogg",
	//"ambBB41.ogg", "ambBB42.ogg", "ambBB43.ogg", "ambBB44.ogg", "ambBB45.ogg",
	//"ambBB46.ogg", "ambBB47.ogg", "ambBB48.ogg", "ambBB49.ogg", "ambBB50.ogg"
	};

ambiance::ambiance()
{

	for(int i = 0; i < 10; i++)
		mAmbAA[i].openFromFile(path+ambAAFile[i]);

	for(int i = 0; i < 10; i++)
		mAmbAB[i].openFromFile(path+ambABFile[i]);

	for(int i = 0; i < 7; i++)
		mAmbBA[i].openFromFile(path+ambBAFile[i]);

	for(int i = 0; i < 9; i++)
		mAmbBB[i].openFromFile(path+ambBBFile[i]);

		// GLOBAL VARIABLES //
	frameCounter = 0; // <----------------------------------------------------- LINK TO THE GAME? :)
	ambMaxVolume = 50; // <--------------------------------------------------- LINK TO THE GAME
	ambMadness = 100; // <----------------------------------------------------- LINK TO THE GAME
	//int frameRate = 60; ////////// <<<<<<<<<<< LINK TO FADESPEED?
	
	// VARIABLES AA //
	ambAAVolume = 0;
	ambAADynamics = 0;
	ambAARandom = 0;
	ambAALength = 0;
	ambAAPitch = 0;
	ambAASecCounter = 0;
	ambAAFadeOut = false;
	ambAAFadeSpeed = 0;
	ambAAIntToFloat = 0;

	// VARIABLES AB //
	ambABVolume = 0;
	ambABDynamics = 0;
	ambABRandom = 0;
	ambABLength = 0;
	ambABPitch = 0;
	ambABSecCounter = 0;
	ambABFadeOut = false;
	ambABFadeSpeed = 0;
	ambABIntToFloat = 0;

	// VARIABLES BA //
	ambBAVolume = 0;
	ambBADynamics = 0;
	ambBARandom = 0;
	ambBALength = 0;
	ambBAPitch = 0;
	ambBASecCounter = 0;
	ambBAFadeOut = false;
	ambBAFadeSpeed = 0;
	ambBAIntToFloat = 0;

	// VARIABLES BB //
	ambBBVolume = 0;
	ambBBDynamics = 0;
	ambBBRandom = 0;
	ambBBLength = 0;
	ambBBPitch = 0;
	ambBBSecCounter = 0;
	ambBBFadeOut = false;
	ambBBFadeSpeed = 0;
	ambBBIntToFloat = 0;

	

	// MUSIC INSTANCES AA //
	ambAA.setVolume(0);
	ambAA.setLoop(true); 

	// MUSIC INSTANCE AB //
	ambAB.setVolume(0);
	ambAB.setLoop(true); 

	// MUSIC INSTANCE BA //
	ambBA.setVolume(0);
	ambBA.setLoop(true); 

	// MUSIC INSTANCE BB //
	ambBB.setVolume(0);
	ambBB.setLoop(true); 
	// RAND TIME & ARRAYLENGTH DEFINITION //
		srand (time(0));	
}

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

ambiance::~ambiance()
{
}

void ambiance::tick()
{
	frameCounter++;

		if (frameCounter>60)
		{
			frameCounter = 0;

			// COUNTERS ABCD //
			ambAASecCounter++;
			ambABSecCounter++;
			ambBASecCounter++;
			ambBBSecCounter++;

			// IF NOT PLAYING AA ///////////////////////////////////////////////////
			
			if (ambAA.getStatus() == 0)
			{
				// FILE SELECTOR //
				ambAARandom = rand()% ARRAY_SIZE(ambAAFile);
				//ambAA.openFromFile(path+ambAAFile[ambAARandom]);
				//ambAA = mAmbAA[ambAARandom];

				// VOLUME RESET //
				mAmbAA[ambAARandom].setVolume(0);
				ambAAVolume = 0;
				ambAADynamics = 100000; //TRIGGER

				// LENGTH //
				ambAALength = rand() % 30 + 30;
				ambAASecCounter = 0;

				// FADE //
				ambAAFadeSpeed = rand()% 2 + 3;
				ambAAFadeOut = false;

				// PITCH //
				ambAAPitch = rand() % 100;
				ambAAPitch = ambAAPitch/200+0.75;
				mAmbAA[ambAARandom].setPitch(ambAAPitch);
				
				// PLAY //
				mAmbAA[ambAARandom].play();
			}

			// IF NOT PLAYING AB /////////////////////////////////////////////////////////
			if (ambAB.getStatus() == 0)
			{
				// FILE SELECTOR //
				ambABRandom = rand()% ARRAY_SIZE(ambABFile);
				//ambAB.openFromFile(path+ambABFile[ambABRandom]);
				//ambAB = mAmbAB[ambABRandom];

				// VOLUME RESET //
				mAmbAB[ambABRandom].setVolume(0);
				ambABVolume = 0;
				ambABDynamics = 100000; //TRIGGER

				// LENGTH //
				ambABLength = rand() % 30 + 30;
				ambABSecCounter = 0;

				// FADE //
				ambABFadeSpeed = rand()% 2 + 3;
				ambABFadeOut = false;

				// PITCH //
				ambABPitch = rand() % 100;
				ambABPitch = ambABPitch/200+0.75;
				mAmbAB[ambABRandom].setPitch(ambABPitch);
				
				// PLAY //
				mAmbAB[ambABRandom].play();
			}
			
			// IF NOT PLAYING BA /////////////////////////////////////////////////////////

			if (ambBA.getStatus() == 0 && ambMadness > 50 && rand() % 20 == 0 && ambBASecCounter > rand()%20+20)
			{
				// FILE SELECTOR //
				ambBARandom = rand()% ARRAY_SIZE(ambBAFile);
				//ambBA.openFromFile(path+ambBAFile[ambBARandom]);
				//ambBA = mAmbBA[ambBARandom];

				// VOLUME RESET //
				mAmbBA[ambBARandom].setVolume(0);
				ambBAVolume = 0;
				ambBADynamics = 100000; //TRIGGER

				// LENGTH //
				ambBALength = rand() % 20 + 20;
				ambBASecCounter = 0;

				// FADE //
				ambBAFadeSpeed = rand()% 3 + 3;
				ambBAFadeOut = false;

				// PITCH //
				ambBAPitch = rand() % 100;
				ambBAPitch = ambBAPitch/200+0.75;
				mAmbBA[ambBARandom].setPitch(ambBAPitch);

				// PLAY //
				mAmbBA[ambBARandom].play();

				// BB /////////////////////////////////////////////////////////

				// FILE SELECTOR //
				ambBBRandom = rand()% ARRAY_SIZE(ambBBFile);
				//ambBB.openFromFile(path+ambBBFile[ambBBRandom]);
				//ambBB = mAmbBB[ambBBRandom];

				// VOLUME RESET //
				mAmbBB[ambBBRandom].setVolume(0);
				ambBBVolume = 0;
				ambBBDynamics = 100000; //TRIGGER

				// LENGTH //
				ambBBLength = ambAALength - 5 - rand()% 5;
				ambBBSecCounter = 0;

				// FADE //
				ambBBFadeSpeed = ambBAFadeSpeed * 0.75;
				ambBBFadeOut = false;

				// PITCH //
				ambBBPitch = rand() % 100;
				ambBBPitch = ambBBPitch/200+0.75;
				mAmbBB[ambBBRandom].setPitch(ambBBPitch);
				
				// PLAY //
				mAmbBB[ambBBRandom].play();
			}
		}

		// FADE AA ////////////////////////////////////////////////////////////////
		
		if (ambAAVolume + ambAAFadeSpeed < ambAADynamics && ambAAFadeOut == false)
		{
			ambAAVolume = ambAAVolume + ambAAFadeSpeed;

			ambAAIntToFloat = ambAAVolume;
			ambAAIntToFloat = ambAAIntToFloat/100*(ambMaxVolume/100);
			mAmbAA[ambAARandom].setVolume(ambAAIntToFloat);

			ambAADynamics = 10000*(ambMadness*0.25/100) + 2500;
		}

		else if (ambAAVolume > ambAADynamics && ambAAFadeOut == false)
		{
			ambAAVolume = ambAAVolume - ambAAFadeSpeed;

			ambAAIntToFloat = ambAAVolume;
			ambAAIntToFloat = ambAAIntToFloat/100*(ambMaxVolume/100);
			mAmbAA[ambAARandom].setVolume(ambAAIntToFloat);

			ambAADynamics = 10000*(ambMadness*0.25/100) + 2500;
		}
		if (ambAASecCounter > ambAALength && ambABFadeOut == false)
		{
			ambAAFadeOut = true;

			if (ambAAVolume > ambAAFadeSpeed)
			{
				ambAAVolume = ambAAVolume - ambAAFadeSpeed;

				ambAAIntToFloat = ambAAVolume;
				ambAAIntToFloat = ambAAIntToFloat/100*(ambMaxVolume/100);
				mAmbAA[ambAARandom].setVolume(ambAAIntToFloat);
			}

			if (ambAAVolume <= ambAAFadeSpeed*2)
			{
				ambAAVolume = 0;
				ambAAFadeOut = false;
				mAmbAA[ambAARandom].setVolume(0);
				mAmbAA[ambAARandom].stop();
			}
		}

		// FADE AB ////////////////////////////////////////////////////////////////
		
		if (ambABVolume + ambABFadeSpeed < ambABDynamics && ambABFadeOut == false)
		{
			ambABVolume = ambABVolume + ambABFadeSpeed;

			ambABIntToFloat = ambABVolume;
			ambABIntToFloat = ambABIntToFloat/100*(ambMaxVolume/100);
			mAmbAB[ambABRandom].setVolume(ambABIntToFloat);

			ambABDynamics = 10000*(ambMadness*0.4/100) + 1000;
		}

		else if (ambABVolume > ambABDynamics && ambABFadeOut == false)
		{
			ambABVolume = ambABVolume - ambABFadeSpeed;

			ambABIntToFloat = ambABVolume;
			ambABIntToFloat = ambABIntToFloat/100*(ambMaxVolume/100);
			mAmbAB[ambABRandom].setVolume(ambABIntToFloat);

			ambABDynamics = 10000*(ambMadness*0.4/100) + 1000;
		}

		if (ambABSecCounter > ambABLength && ambAAFadeOut == false)
		{
			ambABFadeOut = true;

			if (ambABVolume > ambABFadeSpeed)
			{
				ambABVolume = ambABVolume - ambABFadeSpeed;

				ambABIntToFloat = ambABVolume;
				ambABIntToFloat = ambABIntToFloat/100*(ambMaxVolume/100);
				mAmbAB[ambABRandom].setVolume(ambABIntToFloat);
			}

			if (ambABVolume <= ambABFadeSpeed*2)
			{
				ambABVolume = 0;
				ambABFadeOut = false;
				mAmbAB[ambABRandom].setVolume(0);
				mAmbAB[ambABRandom].stop();
			}
		}

		// FADE BA ////////////////////////////////////////////////////////////////
		
		if (ambBAVolume + ambBAFadeSpeed < ambBADynamics && ambBAFadeOut == false)
		{
			ambBAVolume = ambBAVolume + ambBAFadeSpeed;

			ambBAIntToFloat = ambBAVolume;
			ambBAIntToFloat = ambBAIntToFloat/100*(ambMaxVolume/100);
			mAmbBA[ambBARandom].setVolume(ambBAIntToFloat);

			ambBADynamics = 10000*((ambMadness-50)*0.60/100) + 500;
		}

		else if (ambBAVolume >  ambBADynamics && ambBAFadeOut == false)
		{
			ambBAVolume = ambBAVolume - ambBAFadeSpeed;

			ambBAIntToFloat = ambBAVolume;
			ambBAIntToFloat = ambBAIntToFloat/100*(ambMaxVolume/100);
			mAmbBA[ambBARandom].setVolume(ambBAIntToFloat);

			ambBADynamics = 10000*((ambMadness-50)*0.50/100) + 1000;
		}

		if (ambBASecCounter > ambBALength)
		{
			ambBAFadeOut = true;

			if (ambBAVolume > ambBAFadeSpeed)
			{
				ambBAVolume = ambBAVolume - ambBAFadeSpeed;

				ambBAIntToFloat = ambBAVolume;
				ambBAIntToFloat = ambBAIntToFloat/100*(ambMaxVolume/100);
				mAmbBA[ambBARandom].setVolume(ambBAIntToFloat);
			}

			if (ambBAVolume <= ambBAFadeSpeed*2)
			{
				ambBAVolume = 0;
				ambBAFadeOut = false;
				mAmbBA[ambBARandom].setVolume(0);
				mAmbBA[ambBARandom].stop();
			}
		}

		// FADE BB ////////////////////////////////////////////////////////////////
		
		if (ambBBVolume + ambBAFadeSpeed < ambBBDynamics && ambBBFadeOut == false)
		{
			ambBBVolume = ambBBVolume + ambBBFadeSpeed;

			ambBBIntToFloat = ambBBVolume;
			ambBBIntToFloat = ambBBIntToFloat/100*((float)ambMaxVolume/100);
			mAmbBB[ambBBRandom].setVolume(ambBBIntToFloat);

			ambBBDynamics = 10000*((ambMadness-75)*0.75/100) + 500;
		}

		else if (ambBBVolume > ambBBDynamics && ambBBFadeOut == false)
		{
			ambBBVolume = ambBBVolume - ambBBFadeSpeed;

			ambBBIntToFloat = ambBBVolume;
			ambBBIntToFloat = ambBBIntToFloat/100*(ambMaxVolume/100);
			mAmbBB[ambBBRandom].setVolume(ambBBIntToFloat);

			ambBBDynamics = 10000*((ambMadness-75)*0.75/100) + 500;
		}

		if (ambBBSecCounter > ambBBLength)
		{
			ambBBFadeOut = true;

			if (ambBBVolume > ambBBFadeSpeed)
			{
				ambBBVolume = ambBBVolume - ambBBFadeSpeed;

				ambBBIntToFloat = ambBBVolume;
				ambBBIntToFloat = ambBBIntToFloat/100*(ambMaxVolume/100);
				ambBB.setVolume(ambBBIntToFloat);
			}

			if (ambBBVolume <= ambBBFadeSpeed*2)
			{
				ambBBVolume = 0;
				ambBBFadeOut = false;
				mAmbBB[ambBBRandom].setVolume(0);
				mAmbBB[ambBBRandom].stop();
			}
		}
}


