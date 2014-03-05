#include "FilHanterare.h"

FilHanterare::FilHanterare(void)
{
	
	/*sf::Texture* t = new sf::Texture;
	assert(sf::Texture::loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768)) != NULL);
	mTexture.push_back(t);
	assert(t->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/hej.png",sf::IntRect(0,0,1152,648)) != NULL);
	mTexture.push_back(t);*/
	for(int i = 0; i <= 99;i++)
		mTexture[i] = new sf::Texture();
	for(int i = 0; i < 9;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();
	

	mTexture[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Normal_Spritesheet.png",sf::IntRect(0,0,4096,1024));
	mTexture[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/3 - Inomhus Bg.png",sf::IntRect(0,0,7140,1080));
	mTexture[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level1/Level1.png",sf::IntRect(0,0,8864,3240));
	mTexture[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level2/Level2.png",sf::IntRect(0,0,8000,340));

	
	
	mTexture[21]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Monster 1/Monster1_Spritesheet.png",sf::IntRect(0,0,2048,2048));
	mTexture[22]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy2.png",sf::IntRect(0,0,1024,256));
	mTexture[23]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/D�rr.png",sf::IntRect(0,0,256,256));
	mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Trashcan.png",sf::IntRect(0,0,256,256));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Trashcan2.png",sf::IntRect(0,0,1796,720));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));
	mTexture[25]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis/Lewis_Lightsheet.png",sf::IntRect(0,0,4096,512));
	//mTexture[25]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/glow.png",sf::IntRect(0,0,161,129));
	mTexture[26]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/VendingMachine1.png",sf::IntRect(0,0,256,256));
	mTexture[27]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/black.png",sf::IntRect(0,0,1920,1080));
	mTexture[28]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Ryan/Ryan_Spritesheet.png",sf::IntRect(0,0,1024,256));
	mTexture[29]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Magda/Magda_SpriteSheet.png",sf::IntRect(0,0,2048,256));

	//Intro
	mTexture[30]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/1 - Utomhus 1.png",sf::IntRect(0,0,7140,1080));
	mTexture[31]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/F�rgrundsprops.png",sf::IntRect(0,0,7140,1080));
	mTexture[32]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 1.png",sf::IntRect(0,0,1536,1080));
	mTexture[33]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/Parallax 2.png",sf::IntRect(0,0,3471,1080));

	mTexture[34]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/GUI/StaticGUI/mobil.png",sf::IntRect(0,0,354,177));

	mTexture[35]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/D�rrar/D�rrar SpriteSheet.png",sf::IntRect(0,0,2048,512));
	mTexture[36]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/D�rrar/Hiss Spritesheet.png",sf::IntRect(0,0,8192,256));

	//Intro fors.
	mTexture[37]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/2 - Utomhus 2.png",sf::IntRect(0,0,7140,1080));
	mTexture[38]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/Svart Lager.png",sf::IntRect(0,0,7140,1080));
	mTexture[39]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Prologue/Desk.png",sf::IntRect(0,0,198,160));
	mTexture[40]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/CharLight.png",sf::IntRect(0,0,512,256));
	mTexture[41]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/GUI/AnimatedGUI/Cellphone_GUI.png",sf::IntRect(0,0,1024,1080));
	mTexture[42]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/GUI/AnimatedGUI/Cellphone_lines_GUI.png",sf::IntRect(0,0,1024,1080));

	mTexture[43]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lamp/Level2_Lamp_Lightsheet.png",sf::IntRect(0,0,4096,300));
	mTexture[44]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lamp/Level2_Lamp_Spritesheet.png",sf::IntRect(0,0,4096,300));
	
	mSoundBuffer[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/death.wav");
	mSoundBuffer[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/lewis hall walking slow 2(with clothing).wav");
	mSoundBuffer[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav");
	mSoundBuffer[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 attack 1 new1.wav");
	mSoundBuffer[4]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 slime walk1 new1.wav");
	mSoundBuffer[5]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 walk 2 new 1.wav");
	mSoundBuffer[6]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/monster 1 morph 1 new1.wav");
	mSoundBuffer[7]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/ryan idle1 new 1.wav");
	mSoundBuffer[8]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/magda bed idle 1.wav");
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
	if(ID <= 8)
		return mSoundBuffer[ID];
}
