#include "FilHanterare.h"


FilHanterare::FilHanterare(void)
{
	
	/*sf::Texture* t = new sf::Texture;
	assert(sf::Texture::loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768)) != NULL);
	mTexture.push_back(t);
	assert(t->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/hej.png",sf::IntRect(0,0,1152,648)) != NULL);
	mTexture.push_back(t);*/
	for(int i = 0; i < 5;i++)
		mTexture[i] = new sf::Texture();
	for(int i = 0; i < 4;i++)
		mSoundBuffer[i] = new sf::SoundBuffer();

	mTexture[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768));
	mTexture[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/DubbelMap1.jpg",sf::IntRect(0,0,1152,1296));
	mTexture[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy.png",sf::IntRect(0,0,960,240));
	mTexture[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Dörr.png",sf::IntRect(0,0,256,256));
	mTexture[4]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));

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
	if(ID <= 4)
		return mTexture[ID];
}

sf::SoundBuffer* FilHanterare::getSound(int ID)
{
	if(ID <= 3)
		return mSoundBuffer[ID];
}
