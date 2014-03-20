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
	for(int i = 0; i <= 9;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();
	


	mTexture[0]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Normal_Spritesheet.png",sf::IntRect(0,0,4096,1280));
	mTexture[1]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/3 - Inomhus Bg.png",sf::IntRect(0,0,3296,625));
	mTexture[2]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level1/Level1.png",sf::IntRect(0,0,8864,3240));
	mTexture[3]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level2/Level2.png",sf::IntRect(0,0,8192,300));
	mTexture[4]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level3/Level_3_1.png",sf::IntRect(0,0,8192,600));
	mTexture[5]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level3/Level_3_2.png",sf::IntRect(0,0,8192,1200));
	mTexture[6]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Level4/Level 4.png",sf::IntRect(0,0,8192,1200));

	mTexture[20]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Respawn Rum/Lewis Sjukrum.png",sf::IntRect(0,0,600,300));
	
	
	mTexture[21]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Monster 1/Monster1_Spritesheet.png",sf::IntRect(0,0,2048,2048));
	//mTexture[22]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/enemy2.png",sf::IntRect(0,0,1024,256));
	mTexture[22]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Monster_inte_bubb_spritesheet.png",sf::IntRect(0,0,4096,1024));
	mTexture[23]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörr.png",sf::IntRect(0,0,256,256));
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
	mTexture[32]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 1.png",sf::IntRect(0,0,1536,790));
	mTexture[33]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 2.png",sf::IntRect(0,0,3471,790));

	mTexture[34]->loadFromFile(path+"LucidProject/Resources/Graphics/GUI/StaticGUI/mobil.png",sf::IntRect(0,0,354,177));

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
	mTexture[49]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Misc/StairwayUp.png",sf::IntRect(0,0,312,244));
	mTexture[50]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Misc/StairwayDown.png",sf::IntRect(0,0,312,244));
	mTexture[51]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/HalfdomeLamp_Sprite.png",sf::IntRect(0,0,512,256));
	mTexture[52]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/HalfdomeLamp_Lightmap.png",sf::IntRect(0,0,512,256));

	mTexture[53]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/E placeholder Spritesheet.png",sf::IntRect(0,0,128,64));
	mTexture[54]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Q placeholder Spritesheet.png",sf::IntRect(0,0,128,64));

	mTexture[55]->loadFromFile(path+"LucidProject/Resources/Graphics/Backgrounds/Prologue/Svart Lager.png", sf::IntRect(0, 0, 7140, 1080));

	mTexture[56]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Lysrör liten.png",sf::IntRect(0,0,451,440));
	mTexture[57]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lamp/Lysrör.png",sf::IntRect(0,0,869,451));
	mTexture[58]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Lewis/LewisCellphone_Lightsheet.png",sf::IntRect(0,0,4096,512));
	mTexture[59]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/F placeholder Spritesheet.png",sf::IntRect(0,0,128,64));

	mTexture[60]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/vattentavla/vattentavla1.png",sf::IntRect(0,0,128,256));
	mTexture[61]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/vattentavla/vattentavlaSpritesheet.png",sf::IntRect(0,0,384,256));
	mTexture[62]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Vatten/vatten_spritesheet.png",sf::IntRect(0,0,2048,256));
	mTexture[63]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Brus_spritesheet.png",sf::IntRect(0,0,7680,1080));

	mTexture[64]->loadFromFile(path+"LucidProject/Resources/Graphics/Animations/Dörrar/Dörrar SpriteSheet 2.png",sf::IntRect(0,0,2048,512));

	
	mSoundBuffer[0]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/death.wav");
	mSoundBuffer[1]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/lewis hall walking slow 2(with clothing).wav");
	mSoundBuffer[2]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2.wav");
	mSoundBuffer[3]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 attack 1 new1.wav");
	mSoundBuffer[4]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 slime walk1 new1.wav");
	mSoundBuffer[5]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 walk 2 new 1.wav");
	mSoundBuffer[6]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 morph 1 new1.wav");
	mSoundBuffer[7]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/ryan idle1 new 1.wav");
	mSoundBuffer[8]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/magda bed idle 1.wav");
	mSoundBuffer[9]->loadFromFile(path+"LucidProject/Resources/Sound/SoundFX/MONO sound fx/lewis flashlight ON .wav");

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
	if(ID <= 9)
		return mSoundBuffer[ID];
}
