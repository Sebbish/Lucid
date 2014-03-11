#ifndef DIALOG_H
#define DIALOG_H
#include <string>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <fstream>
#include <vector>
class Dialog
{
public:
	Dialog(sf::Texture &texture);
	~Dialog();
	void tick(sf::View* view);
	void render(sf::RenderWindow* target);
	void loadFile(std::string name,int ID);
	void nextLine();
	void newMap(int mapID);
	void getLine(int line);
	void setDraw(bool draw);//funktion där man anger om man vill att texten ska visas eller inte
	bool getDraw()const;
private:
	void playSound(int ID);
	sf::Font mFont;
	sf::Text mText;
	bool mDraw;//bool om man ska rita ut text,
	std::vector<std::string> mStrings;
	std::vector<sf::Music*> mSounds;
	int mLineNumber;
	sf::Texture &mTexture;
};
#endif

