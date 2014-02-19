#include "Mobil.h"


Mobil::Mobil(sf::Texture* texture,SaveLoad* SL, int mapID):
	mTexture(texture),mActivated(false),mLoad(false),mSave(false),mMapID(mapID),mSL(SL)
{
	//fixar hitbox på knappar
	for(int i = 0; i < 7; i++)
	{
		mApp[i].height = mApp[i].height = 1;

		if(i == 0 || i == 1 ||i == 4)
		{
			mApp[i].left = 135;
		}else if(i == 2 ||i == 5)
		{
			mApp[i].left = 300;
		}else
		{
			mApp[i].left = 500;
		}

		if(i == 0)
		{
			mApp[i].top = 535;
		}else if(i == 1 || i  == 2 || i == 3)
		{
			mApp[i].top = 650;
		}else
		{
			mApp[i].top = 800;
		}

	}
	mApp[7].left = mApp[8].left = mApp[9].left = 285;
	mApp[7].top = 200;
	mApp[8].top = 400;
	mApp[9].top = 600;

}



Mobil::~Mobil()
{
}

//sparar
void Mobil::save(int mapID)
{
	if(mActiveAppID >= 7)
		mSL->save(mActiveAppID-7,mSaveName,mapID);
}

//retunerar om mobilen väntar på input
bool Mobil::getSkriver()const
{
	return mSkriverSaveSlotText;
}

//ställer in om mobilen ska vänta på input
void Mobil::setWritingText(bool text)
{
	mSkriverSaveSlotText = text;
}

//lägger till tecken till spar stringen
void Mobil::addTextToSaveSlot(char tecken)
{
	mSaveName += tecken;
}

//aktiverar mobilen och sätter rätt position
void Mobil::activate(sf::View* view,int mapID)
{
	mRect.height = view->getSize().y;
	mRect.width = mRect.height*((float)(mTexture->getSize().x/3)/(float)mTexture->getSize().y);
	mRect.left = view->getCenter().x-mRect.width/2;
	mRect.top = view->getCenter().y-mRect.height/2;
	mActivated = true;
	mActiveAppID = 0;
	mMapID = mapID;
}

//avaktiverar mobilen
void Mobil::deactivate()
{
	mActivated = false;
}

//markerar nästa app
void Mobil::nextApp()
{
	if(!mLoad && !mSave)
	{
		if(mActiveAppID <= 5)
			mActiveAppID++;
		else
			mActiveAppID = 0;
	}else
	{
		if(mActiveAppID <= 8)
			mActiveAppID++;
		else
			mActiveAppID = 7;
	}
}

//markerar föregående app
void Mobil::lastApp()
{
	if(!mLoad && !mSave)
	{
		if(mActiveAppID >= 1)
			mActiveAppID--;
		else
			mActiveAppID = 6;
	}else
	{
		if(mActiveAppID >= 8)
			mActiveAppID--;
		else
			mActiveAppID = 9;
	}
}

//retunerar ID till den markerade appen, vissa aktiverar vissa saker i mobilen
int Mobil::getActiveAppID()
{
	if(mActiveAppID == 1)
		mSave = true;
	else if (mActiveAppID == 2)
		mLoad = true;

	if((mActiveAppID == 7 || mActiveAppID == 8 || mActiveAppID == 9) && mSave)
	{
		mSaveName = "";
		mSkriverSaveSlotText = true;
	}

	return mActiveAppID;
}

//resetar mobilen
void Mobil::reset()
{
	mSave = mLoad = mSkriverSaveSlotText = false;
	mActiveAppID = 0;
}

//retunerar om mobilen är på väg/ska ladda
bool Mobil::IWantToLoad()
{
	return mLoad;
}

//retunerar om mobilen är aktiv
bool Mobil::getActivate()const
{
	return mActivated;
}

//uppdatera
void Mobil::tick()
{
	if(mLoad || mSave)
	{
		if(mActiveAppID <= 6)
			mActiveAppID = 7;
	}else if(mActiveAppID >= 7)
			mActiveAppID = 0;
}

//renderar
void Mobil::render(sf::RenderWindow* target)
{
	if(mActivated)
	{

		sf::RectangleShape rs;
		rs.setPosition(mRect.left,mRect.top);
		rs.setSize(sf::Vector2f(mRect.width,mRect.height));
		rs.setTexture(mTexture);
		if(mLoad || mSave)
			rs.setTextureRect(sf::IntRect(118,0,118,177));
		else
			rs.setTextureRect(sf::IntRect(0,0,118,177));
		target->draw(rs);


		if(mLoad || mSave)
		{
			sf::Font f;
			f.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf");
			sf::Text t;
			t.setColor(sf::Color::White);
			t.setCharacterSize(20);
			t.setFont(f);
			t.setPosition(mRect.left+mApp[7].left-200,mRect.top+mApp[7].top-100);
			t.setString(mSL->loadText(0));
			target->draw(t);

			t.setPosition(mRect.left+mApp[8].left-200,mRect.top+mApp[8].top-50);
			t.setString(mSL->loadText(1));
			target->draw(t);

			t.setPosition(mRect.left+mApp[9].left-200,mRect.top+mApp[9].top-30);
			t.setString(mSL->loadText(2));
			target->draw(t);
		}


		sf::RectangleShape rss;
		rss.setPosition(mRect.left+mApp[mActiveAppID].left,mRect.top+mApp[mActiveAppID].top);
		rss.setSize(sf::Vector2f(10,10));
		rss.setFillColor(sf::Color::Green);
		target->draw(rss);
	}
}