#ifndef FILHANTERARE_H
#define FILHANTERARE_H
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <vector>
#include <assert.h>
class FilHanterare
{
public:
	FilHanterare();
	~FilHanterare();
	sf::Texture* getTexture(int ID)const;
	void getSound(int ID);
private:
	sf::Texture *mTexture[5];
};
#endif

