#include "Dialog.h"


Dialog::Dialog():
	mDraw(false)
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

void Dialog::nextLine()
{
	mLineNumber++;
	if(mLineNumber <= mStrings.size()-1)
		mText.setString(mStrings[mLineNumber]);
	else
		mDraw = false;
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

bool Dialog::getDraw()const
{
	return mDraw;
}

void Dialog::tick(sf::View* view)
{
	mText.setPosition(view->getCenter().x-view->getSize().x/4,view->getCenter().y+view->getSize().y/3);
}

void Dialog::render(sf::RenderTexture* target)
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
