#ifndef CRED_H
#define CRED_H
#include <string>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
class cred
{
public:
	cred();
	~cred();
	bool tick();
	void render(sf::RenderWindow &target);
private:
	sf::Music m;
	sf::Text t;
	sf::Font f;
	std::string text;
	bool end;
};
#endif

