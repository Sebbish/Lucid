#ifndef DIALOG_H
#define DIALOG_H
#include <string>
#include <sstream>
#include "SFML\Graphics.hpp"
#include <fstream>
class Dialog
{
public:
	Dialog();
	~Dialog();
	void tick(sf::View* view);
	void render(sf::RenderTexture* target);
	void getLine(int line);
	void setDraw(bool draw);//funktion där man anger om man vill att texten ska visas eller inte
private:
	sf::Font mFont;
	sf::Text mText;
	bool mDraw;//bool om man ska rita ut text
};
#endif

