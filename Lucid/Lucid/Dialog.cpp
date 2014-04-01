#include "Dialog.h"

//laddar in font,sätter färg och tillfällig position
Dialog::Dialog(sf::Texture &texture):
	mDraw(false),mTexture(texture)
{
	if(!mFont.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf"))
	{
		//Något fel
	}
	mText.setFont(mFont);
	mText.setPosition(0,0);
	mText.setColor(sf::Color::Red);
	mRS.setSize(sf::Vector2f(960,200));
	mRS.setTexture(&mTexture);
}


Dialog::~Dialog()
{
	while(mSounds.size() >= 1)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
}

//laddar angivna text filen och lägger den i en string "vector" och börjar visa dialogen
void Dialog::loadFile(std::string name,int ID)
{
	for(int i = mStrings.size()-1; i >= 0; i--)
		mStrings.pop_back();
	std::fstream mFStream("../../../LucidProject/Resources/Dialog/"+name+".txt");
	std::string temp;
	while(getline(mFStream,temp))
		mStrings.push_back(temp);
	mLineNumber = 0;
	mText.setString(mStrings[mLineNumber]);
	mDraw = true;
	playSound(ID);
}

void Dialog::newMap(int mapID)
{
	while(mSounds.size() >= 1)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
	if(mapID == 3)
	{
		mSounds.push_back(new sf::Music);
		mSounds[mSounds.size()-1]->openFromFile("../../../LucidProject/Resources/Sound/voicemail/boo 09 ( high sanity).ogg");
	}
}

void Dialog::playSound(int ID)
{
	for(auto i:mSounds)
		i->stop();
	if(ID <= mSounds.size()-1 && ID >= 0)
		mSounds[ID]->play();
}

//går till nästa "rad" i dialogen
void Dialog::nextLine()
{
	mLineNumber++;
	if(mLineNumber <= mStrings.size()-1)
		mText.setString(mStrings[mLineNumber]);
	else
		mDraw = false;
}

//bool för om dialogen ska ritas eller inte
void Dialog::setDraw(bool draw)
{
	mDraw = draw;
	
}

//retunerar om dialogen ritas
bool Dialog::getDraw()const
{
	return mDraw;
}

//sätter positionen utfrån cameran
void Dialog::tick(sf::View* view)
{
	if(!mDraw)
		for(auto i:mSounds)
			i->stop();
}

//renderar dialogen på en vit rectangel
void Dialog::render(sf::RenderWindow* target)
{
	if(mDraw)
	{
		
		mRS.setPosition(target->getPosition().x+target->getSize().x/2-mRS.getSize().x/2,target->getSize().y-mRS.getSize().y);
		mRS.setFillColor(sf::Color::White);
		
		target->draw(mRS);
		mText.setPosition(mRS.getPosition().x+270,mRS.getPosition().y+50);
		target->draw(mText);
	}
}
