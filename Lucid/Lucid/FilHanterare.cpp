#include "FilHanterare.h"


FilHanterare::FilHanterare(void)
{
	
	/*sf::Texture* t = new sf::Texture;
	assert(sf::Texture::loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768)) != NULL);
	mTexture.push_back(t);
	assert(t->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/hej.png",sf::IntRect(0,0,1152,648)) != NULL);
	mTexture.push_back(t);*/
	for(int i = 0; i <= 24;i++)
		mTexture[i] = new sf::Texture();
	for(int i = 0; i < 4;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();
	
	mTexture[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768));
	mTexture[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level1.png",sf::IntRect(0,0,8864,3240));
	mTexture[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/Level2.png",sf::IntRect(0,0,8000,340));
	mTexture[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Ryan_Spritesheet.png",sf::IntRect(0,0,1024,256));
	mTexture[4]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Magda_SpriteSheet.png",sf::IntRect(0,0,2048,256));
	mTexture[21]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy.png",sf::IntRect(0,0,960,240));
	mTexture[22]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy2.png",sf::IntRect(0,0,1024,256));
	mTexture[23]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/D�rr.png",sf::IntRect(0,0,256,256));
	mTexture[24]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));

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
	if(ID <= 24)
		return mTexture[ID];
}

sf::SoundBuffer* FilHanterare::getSound(int ID)
{
	if(ID <= 3)
		return mSoundBuffer[ID];
}
