#include "Dialog.h"


Dialog::Dialog():
	mDraw(true)
{
	if(!mFont.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf"))
	{
		//Något fel
	}
	mText.setFont(mFont);
	mText.setPosition(0,0);
	mText.setColor(sf::Color::Red);
	getLine(2);
}


Dialog::~Dialog()
{
}

void Dialog::getLine(int line)
{
	std::fstream mFStream("P:/Downloads/LucidProject/Resources/Dialog/Dialog.txt");
	std::string mTempText,mTemp;
	mFStream.seekg(std::ios::beg);
    for(int i=0; i < line - 1; ++i){
        mFStream.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
	std::getline(mFStream,mTempText);


	std::stringstream ss(mTempText.c_str());
	while(std::getline(ss,mTempText,','))
	{
		if(mTemp == "")
			mTemp = mTempText;
		else
			mTemp = mTemp+'\n'+mTempText;
	}
	mText.setString(mTemp);
}

void Dialog::setDraw(bool draw)
{
	mDraw = draw;
}

void Dialog::tick(sf::View* view)
{
	mText.setPosition(view->getCenter().x-view->getSize().x/2,view->getCenter().y+view->getSize().y/3);
}

void Dialog::render(sf::RenderTexture* target)
{
	if(mDraw)
	{
		sf::RectangleShape mRS;
		mRS.setPosition(mText.getPosition().x,mText.getPosition().y);
		mRS.setSize(sf::Vector2f(1920,200));
		mRS.setFillColor(sf::Color::White);
		target->draw(mRS);
		target->draw(mText);
	}
}
