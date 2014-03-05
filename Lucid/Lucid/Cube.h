#ifndef CUBE_H
#define CUBE_H
#include "SFML\Graphics.hpp"
class Cube
{
public:
	enum direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Cube(sf::FloatRect &rect,bool leader,bool fruit,sf::Texture& t,sf::FloatRect maxSize);
	~Cube();

	//move to this rect
	sf::FloatRect& getRect();
	void setRect(sf::FloatRect& rect);
	void setDirection(direction d);
	void tick(sf::FloatRect& rect);
	void render(sf::RenderWindow& target, int animationX);
private:
	direction mD, mNextD;
	sf::FloatRect mRect;
	sf::FloatRect maxSize;
	bool mLeader;
	bool mFruit;
	sf::Texture &t;
};
#endif

