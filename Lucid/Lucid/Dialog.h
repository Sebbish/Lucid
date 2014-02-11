#ifndef DIALOG_H
#define DIALOG_H
#include <string>
#include <sstream>
#include "SFML\Graphics.hpp"
#include <fstream>
#include <vector>
class Dialog
{
public:
	Dialog();
	~Dialog();
	void tick(sf::View* view);
	void render(sf::RenderTexture* target);
	void loadFile(std::string name);
	void nextLine();
	void getLine(int line);
	void setDraw(bool draw);//funktion där man anger om man vill att texten ska visas eller inte
	bool getDraw()const;
private:
	sf::Font mFont;
	sf::Text mText;
	bool mDraw;//bool om man ska rita ut text,
	std::vector<std::string> mStrings;
	int mLineNumber;
};
#endif

