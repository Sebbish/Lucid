#include "FilHanterare.h"

FilHanterare::FilHanterare(void)
{
	
	/*sf::Texture* t = new sf::Texture;
	assert(sf::Texture::loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768)) != NULL);
	mTexture.push_back(t);
	assert(t->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/hej.png",sf::IntRect(0,0,1152,648)) != NULL);
	mTexture.push_back(t);*/
	for(int i = 0; i <= 34;i++)
		mTexture[i] = new sf::Texture();
	for(int i = 0; i < 4;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();
	
	mTexture[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Spritesheet.png",sf::IntRect(0,0,2116,529));
	mTexture[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Intro/Bakgrund och korridor.png",sf::IntRect(0,0,7140,1080));
	mTexture[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level11.png",sf::IntRect(0,0,8864,1860));
	mTexture[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level2.png",sf::IntRect(0,0,8000,340));


	
	
	mTexture[21]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Monster1_Spritesheet.png",sf::IntRect(0,0,2048,2048));
	mTexture[22]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy2.png",sf::IntRect(0,0,1024,256));
	mTexture[23]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Dörr.png",sf::IntRect(0,0,256,256));
	mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Trashcan.png",sf::IntRect(0,0,256,256));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Trashcan2.png",sf::IntRect(0,0,1796,720));
	//mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));
	mTexture[25]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/glow.png",sf::IntRect(0,0,161,129));
	mTexture[26]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/VendingMachine1.png",sf::IntRect(0,0,256,256));
	mTexture[27]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/black.png",sf::IntRect(0,0,1920,1080));
	mTexture[28]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Ryan_Spritesheet.png",sf::IntRect(0,0,1024,256));
	mTexture[29]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Magda_SpriteSheet.png",sf::IntRect(0,0,2048,256));

	//Intro
	mTexture[30]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Intro/Bakgrundsprops.png",sf::IntRect(0,0,7140,1080));
	mTexture[31]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Intro/Förgrundsprops.png",sf::IntRect(0,0,7140,1080));
	mTexture[32]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Intro/HusParallax1.png",sf::IntRect(0,0,1308,1080));
	mTexture[33]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Intro/HusParallax2.png",sf::IntRect(0,0,887,1080));
	mTexture[34]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/GUI/StaticGUI/mobil.png",sf::IntRect(0,0,354,177));

	mSoundBuffer[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/death.wav");
	mSoundBuffer[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/walk.wav");
	mSoundBuffer[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/protal.wav");
	mSoundBuffer[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Sound/jaga.wav");
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
	if(ID <= 34)
		return mTexture[ID];
}

sf::SoundBuffer* FilHanterare::getSound(int ID)
{
	if(ID <= 3)
		return mSoundBuffer[ID];
}
