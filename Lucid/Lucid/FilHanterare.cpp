#include "FilHanterare.h"

FilHanterare::FilHanterare(void)
{
	std::string path = "../../../";
	//std::string path = "P://Downloads/";
	/*sf::Texture* t = new sf::Texture;
	assert(sf::Texture::loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768)) != NULL);
	mTexture.push_back(t);
	assert(t->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/hej.png",sf::IntRect(0,0,1152,648)) != NULL);
	mTexture.push_back(t);*/
	for(int i = 0; i <= 99;i++)
		mTexture[i] = new sf::Texture();
	for(int i = 0; i <= 29;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();
	


	mTexture[0]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Normal_Spritesheet.png",sf::IntRect(0,0,4096,1280));
	mTexture[1]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/3 - Inomhus Bg.png",sf::IntRect(0,0,3296,625));
	mTexture[2]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level1/Level1.png",sf::IntRect(0,0,8864,3240));
	mTexture[3]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level2/Level2.png",sf::IntRect(0,0,8192,300));
	mTexture[4]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level3/Level_3_1.png",sf::IntRect(0,0,8192,600));
	mTexture[5]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level3/Level_3_2.png",sf::IntRect(0,0,8192,1200));
	mTexture[6]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level4/Level 4,1.png",sf::IntRect(0,0,5534,1200));
	mTexture[7]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level4/Level 4,2.png",sf::IntRect(0,0,4096,1200));
	//Final corridor efter 3:e båtscenen [16]
	mTexture[8]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Magdas rum/Magda Sjukrum.png",sf::IntRect(0,0,600,300));
	mTexture[9]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Epilogue/3 - Inomhus Bg.png", sf::IntRect(0, 0, 3296, 625));
	mTexture[10]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/FinalCorridor/FinalCorridor.png", sf::IntRect(0, 0, 2048, 300));
	mTexture[11]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Respawn Rum/Lewis Sjukrum.png",sf::IntRect(0,0,600,300));
	mTexture[12]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Hiss1.png",sf::IntRect(0,0,300,256));
	mTexture[14]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/LevelBoat2/Level_Boat_2.png",sf::IntRect(0,0,4098,256));
	mTexture[13]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/LevelBoat1/båtscen ute(1).png",sf::IntRect(0,0,1362,696));

	mTexture[16]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/FinalCorridor/FinalCorridor.png", sf::IntRect(0, 0, 2048, 300));

	mTexture[20]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Respawn Rum/Lewis Sjukrum.png",sf::IntRect(0,0,600,300));

	
	
	mTexture[21]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Monster 1/Monster1_Spritesheet.png",sf::IntRect(0,0,2048,2048));
	//mTexture[22]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/enemy2.png",sf::IntRect(0,0,1024,256));
	mTexture[22]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Monster_inte_bubb_spritesheet.png",sf::IntRect(0,0,4096,1024));
	//mTexture[23]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörr.png",sf::IntRect(0,0,256,256));
	mTexture[24]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Trashcan.png",sf::IntRect(0,0,256,256));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Trashcan2.png",sf::IntRect(0,0,1796,720));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));

	mTexture[25]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Lightsheet.png",sf::IntRect(0,0,4096,512));

	//mTexture[25]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/glow.png",sf::IntRect(0,0,161,129));
	mTexture[26]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/VendingMachine1.png",sf::IntRect(0,0,256,256));
	mTexture[27]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/black.png",sf::IntRect(0,0,1920,1080));
	mTexture[28]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Ryan/Ryan_Spritesheet.png",sf::IntRect(0,0,1024,256));
	mTexture[29]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Magda/Magda_SpriteSheet.png",sf::IntRect(0,0,2048,256));

	//Intro
	mTexture[30]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/1 - Utomhus 1.png",sf::IntRect(0,0,2403,625));
	mTexture[31]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Förgrundsprops.png",sf::IntRect(0,0,157,267));
	mTexture[32]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 1.png",sf::IntRect(0,0,1536,650));
	mTexture[33]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 2.png",sf::IntRect(0,0,3471,650));

	//mTexture[34]->loadFromFile(path+"LucidProject/Resources/Graphics/GUI/StaticGUI/mobil.png",sf::IntRect(0,0,354,177));

	mTexture[35]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörrar/Dörrar SpriteSheet.png",sf::IntRect(0,0,2048,512));
	mTexture[36]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörrar/Hiss Spritesheet.png",sf::IntRect(0,0,8192,256));

	//Intro fors.
	mTexture[37]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/2 - Utomhus 2.png",sf::IntRect(0,0,1734,625));
	mTexture[38]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Hiding_Plant.png",sf::IntRect(0,0,256,256));
	mTexture[39]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Desk.png",sf::IntRect(0,0,198,160));
	mTexture[40]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Amb_Lightmap.png",sf::IntRect(0,0,512,300));
	mTexture[41]->loadFromFile(path+"LucidProject/Resources/Graphics/GUI/AnimatedGUI/Cellphone_GUI.png",sf::IntRect(0,0,1024,1080));
	mTexture[42]->loadFromFile(path+"LucidProject/Resources/Graphics/GUI/AnimatedGUI/Cellphone_lines_GUI.png",sf::IntRect(0,0,1024,1080));
	mTexture[43]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Level2_Lamp_Lightsheet.png",sf::IntRect(0,0,4096,300));
	mTexture[44]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Level2_Lamp_Spritesheet.png",sf::IntRect(0,0,4096,300));
	mTexture[45]->loadFromFile(path+"LucidProject/Resources/Graphics/GUI/StaticGUI/Dialoguebox_GUI.png",sf::IntRect(0,0,977,305));

	mTexture[46]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Cardreader_Spritesheet.png",sf::IntRect(0,0,64,32));
	mTexture[47]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Keycard_Sprite.png",sf::IntRect(0,0,32,64));
	mTexture[48]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level1/Level1 Ljus.png",sf::IntRect(0,0,8864,3240));

	mTexture[49]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Misc/StairwayUp.png",sf::IntRect(0,0,256,300));
	mTexture[50]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Misc/StairwayDown.png",sf::IntRect(0,0,256,300));
	mTexture[51]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/HalfdomeLamp_Sprite.png",sf::IntRect(0,0,512,256));
	mTexture[52]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/HalfdomeLamp_Lightmap.png",sf::IntRect(0,0,512,256));

	mTexture[53]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/E placeholder Spritesheet.png",sf::IntRect(0,0,128,64));
	mTexture[54]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Q placeholder Spritesheet.png",sf::IntRect(0,0,128,64));

	mTexture[55]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Svart Lager.png", sf::IntRect(0, 0, 7140, 1080));

	mTexture[56]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Lysrör liten.png",sf::IntRect(0,0,451,440));
	mTexture[57]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Lysrör.png",sf::IntRect(0,0,869,451));

	mTexture[99]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Bewblady_Silhouette.png", sf::IntRect(0, 0, 256, 256));
	mTexture[98]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Businesslady_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[97]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Hipsterpants_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[96]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Moneyback_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[95]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Oldlady_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[94]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Oldman_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[93]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Pojkvasker_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[92]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Texasman_Silhouette.png", sf::IntRect(0, 0, 256, 256));
	mTexture[91]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/MrGreen_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[90]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/LevelBoat1/båtscen ute(2).png", sf::IntRect(0, 0, 51, 534));
	
	mTexture[89]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person1_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[88]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person2_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[87]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person3_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[86]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person4_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[85]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person5_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[84]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Silhouettes/Person6_Spritesheet.png", sf::IntRect(0, 0, 256, 256));
	mTexture[83]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/skeppsgubbesheet.png", sf::IntRect(0, 0, 1024, 256));

	mTexture[68]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/F placeholder Spritesheet.png",sf::IntRect(0,0,128,64));


	mTexture[58]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/LewisCellphone_Lightsheet.png",sf::IntRect(0,0,4096,512));
	mTexture[59]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/F placeholder Spritesheet.png",sf::IntRect(0,0,128,64));


	mTexture[60]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/vattentavla/vattentavla1.png",sf::IntRect(0,0,128,256));
	mTexture[61]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/vattentavla/vattentavlaSpritesheet.png",sf::IntRect(0,0,384,256));
	mTexture[62]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Vatten/vatten_spritesheet.png",sf::IntRect(0,0,2048,256));
	mTexture[63]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Brus_spritesheet.png",sf::IntRect(0,0,7680,1080));


	mTexture[64]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörrar/Dörrar SpriteSheet 2.png",sf::IntRect(0,0,2048,512));

	//Epilogue
	mTexture[65]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Epilogue/1 - Utomhus 1.png", sf::IntRect(0, 0, 2403, 625));
	mTexture[66]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Epilogue/2 - Utomhus 2.png", sf::IntRect(0, 0, 1734, 625));
	mTexture[67]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Epilogue/Parallax 1.png", sf::IntRect(0, 0, 1536, 1080));
	mTexture[68]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Epilogue/parallax 2.png", sf::IntRect(0, 0, 3786, 625));

	mTexture[69]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Captain_Spritesheet.png", sf::IntRect(0, 0, 2048, 512));

	mTexture[70]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Steam/Steam_Spritesheet.png", sf::IntRect(0, 0, 4096, 256));

	mSoundBuffer[0]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/death.wav");

	mSoundBuffer[1]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/lewis hall walking slow 2(with clothing).wav");
	mSoundBuffer[2]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2.wav");
	mSoundBuffer[3]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 attack 1 new1.wav");
	mSoundBuffer[4]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 slime walk1 new1.wav");
	mSoundBuffer[5]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 walk 2 new 1.wav");
	mSoundBuffer[6]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 morph 1 new1.wav");
	mSoundBuffer[28]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/ryan idle1 new 1.wav");
	mSoundBuffer[29]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/magda bed idle 1.wav");
	mSoundBuffer[9]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/lewis flashlight ON .wav");
	mSoundBuffer[10]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/walking up stairs short 2.ogg");

}


FilHanterare::~FilHanterare(void)
{
	for(auto i:mTexture)
		delete i;

	for(auto i:mSoundBuffer)
		delete i;
}

sf::Texture* FilHanterare::getTexture(int ID)const
{
	if(ID <= 99)
		return mTexture[ID];
}

sf::SoundBuffer* FilHanterare::getSound(int ID)
{
	if(ID <= 29)
		return mSoundBuffer[ID];
}
