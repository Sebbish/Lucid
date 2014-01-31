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
	mTexture[0]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Lewis_Insane_Spritesheet.png",sf::IntRect(0,0,1024,768));
	mTexture[1]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Backgrounds/DubbelMap.jpg",sf::IntRect(0,0,1152,1296));
	mTexture[2]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/enemy.png",sf::IntRect(0,0,256,256));
	mTexture[3]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/Dörr.png",sf::IntRect(0,0,256,256));
	mTexture[4]->loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kruka.png",sf::IntRect(0,0,256,256));
}


FilHanterare::~FilHanterare(void)
{
}

sf::Texture* FilHanterare::getTexture(int ID)const
{
	if(ID <= 4)
		return mTexture[ID];
}
