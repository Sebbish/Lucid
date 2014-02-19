#include "Dialog.h"

//laddar in font,s�tter f�rg och tillf�llig position
Dialog::Dialog():
	mDraw(false)
{
	if(!mFont.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf"))
	{
		//N�got fel
	}
	mText.setFont(mFont);
	mText.setPosition(0,0);
	mText.setColor(sf::Color::Red);
}


Dialog::~Dialog()
{
}

//laddar angivna text filen och l�gger den i en string "vector" och b�rjar visa dialogen
void Dialog::loadFile(std::string name)
{
	for(int i = mStrings.size()-1; i >= 0; i--)
		mStrings.pop_back();
	std::fstream mFStream("P:/Downloads/LucidProject/Resources/Dialog/"+name+".txt");
	std::string temp;
	while(getline(mFStream,temp))
		mStrings.push_back(temp);
	mLineNumber = 0;
	mText.setString(mStrings[mLineNumber]);
	mDraw = true;
}

//g�r till n�sta "rad" i dialogen
void Dialog::nextLine()
{
	mLineNumber++;
	if(mLineNumber <= mStrings.size()-1)
		mText.setString(mStrings[mLineNumber]);
	else
		mDraw = false;
}

//bool f�r om dialogen ska ritas eller inte
void Dialog::setDraw(bool draw)
{
	mDraw = draw;
}

//retunerar om dialogen ritas
bool Dialog::getDraw()const
{
	return mDraw;
}

//s�tter positionen utfr�n cameran
void Dialog::tick(sf::View* view)
{
	mText.setPosition(view->getCenter().x-view->getSize().x/4,view->getCenter().y+view->getSize().y/3);
}

//renderar dialogen p� en vit rectangel
void Dialog::render(sf::RenderWindow* target)
{
	if(mDraw)
	{
		sf::RectangleShape mRS;
		mRS.setPosition(mText.getPosition().x-100,mText.getPosition().y);
		mRS.setSize(sf::Vector2f(960,200));
		mRS.setFillColor(sf::Color::White);
		target->draw(mRS);
		target->draw(mText);
	}
}
