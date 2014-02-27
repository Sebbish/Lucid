#include "Mobil.h"


Mobil::Mobil(sf::Texture* texture,sf::Texture* lines):
	mTexture(texture),mLines(lines),mActivated(false)
{
	////fixar hitbox på knappar
	//for(int i = 0; i < 7; i++)
	//{
	//	mApp[i].height = mApp[i].height = 1;

	//	if(i == 0 || i == 1 ||i == 4)
	//	{
	//		mApp[i].left = 135;
	//	}else if(i == 2 ||i == 5)
	//	{
	//		mApp[i].left = 300;
	//	}else
	//	{
	//		mApp[i].left = 500;
	//	}

	//	if(i == 0)
	//	{
	//		mApp[i].top = 535;
	//	}else if(i == 1 || i  == 2 || i == 3)
	//	{
	//		mApp[i].top = 650;
	//	}else
	//	{
	//		mApp[i].top = 800;
	//	}

	//}
	//mApp[7].left = mApp[8].left = mApp[9].left = 285;
	//mApp[7].top = 200;
	//mApp[8].top = 400;
	//mApp[9].top = 600;

	mRect.width = mTexture->getSize().x;
	mRect.height = mTexture->getSize().y;
	snakes = false;
}



Mobil::~Mobil()
{
}



//aktiverar mobilen och sätter rätt position
void Mobil::activate(sf::View* view)
{
	mRect.left = view->getCenter().x-mRect.width/2;
	mRect.top = view->getCenter().y-mRect.height/2;
	mActivated = true;
	mActiveAppID = 0;
}

//avaktiverar mobilen
void Mobil::deactivate()
{
	mActivated = false;
	if(snakes)
	{
		delete s;
		snakes = false;
	}
}

//markerar nästa app
void Mobil::nextApp()
{

		if(mActiveAppID <= 2)
			mActiveAppID++;
		else
			mActiveAppID = 0;
	
}

//markerar föregående app
void Mobil::lastApp()
{

		if(mActiveAppID >= 1)
			mActiveAppID--;
		else
			mActiveAppID = 3;
	
	
}

//retunerar ID till den markerade appen, vissa aktiverar vissa saker i mobilen
int Mobil::getActiveAppID()
{

	return mActiveAppID;
}

//resetar mobilen
void Mobil::reset()
{
	mActiveAppID = 0;
}


void Mobil::ActivateSnakes()
{
	s = new snake(mRect);
	snakes = true;
}

//retunerar om mobilen är aktiv
bool Mobil::getActivate()const
{
	return mActivated;
}

//uppdatera
void Mobil::tick()
{
	 if(mActiveAppID >= 4)
			mActiveAppID = 0;
	 if(snakes)
		 s->tick();


	if(snakes)
		if(s->exitPls())
		{
			snakes = false;
			delete s;
		}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O) && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !snakes)
		ActivateSnakes();

}

//renderar
void Mobil::render(sf::RenderWindow& target)
{
	if(mActivated)
	{
		sf::RectangleShape rs;
		if(!snakes)
		{
			rs.setPosition(mRect.left,mRect.top);
			rs.setSize(sf::Vector2f(mRect.width,mRect.height));
			rs.setTexture(mTexture);
			target.draw(rs);
		}else if(s->getRender())
		{
			target.clear();
			rs.setPosition(mRect.left,mRect.top);
			rs.setSize(sf::Vector2f(mRect.width,mRect.height));
			rs.setTexture(mTexture);
			target.draw(rs);
		}
	
		if(!snakes)
		{

			sf::Font f;
			f.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf");
			sf::Text t,tt,ttt,tttt,t5,t6;
			t.setColor(sf::Color(0,0,0));
			t.setCharacterSize(60);
			t.setFont(f);
			t6 = t5 = tttt = ttt = tt = t;

			t.setString("NEW GAME");
			t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2.0f,t.getGlobalBounds().top + t.getGlobalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+250);
			target.draw(t);

			t.setString("LOAD GAME");
			t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+350);
			target.draw(t);

			t.setString("VOICE MAIL");
			t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+450);
			target.draw(t);

			/*t.setString("SMS");
			t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+550);
			target->draw(t);*/

			t.setString("EXIT GAME");
			t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+550);
			target.draw(t);

			t.setString("<                    >");
			t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t5.getLocalBounds().top + t.getLocalBounds().height/2.0f);
			t.setPosition(mRect.left+mRect.width/2,mRect.top+235+100*mActiveAppID);
			target.draw(t);
		}else if(snakes)
		{
			s->render(target);
		}
		/*tt.setString("LOAD GAME");
		tt.setOrigin(tt.getGlobalBounds().left + tt.getGlobalBounds().width/2.0f,tt.getGlobalBounds().top + tt.getGlobalBounds().height/2.0f);
		tt.setPosition(mRect.left+mRect.width/2,mRect.top+350);m
		target->draw(tt);

		ttt.setString("Voice mail");
		ttt.setOrigin(ttt.getGlobalBounds().left + ttt.getGlobalBounds().width/2.0f,ttt.getGlobalBounds().top + ttt.getGlobalBounds().height/2.0f);
		ttt.setPosition(mRect.left+mRect.width/2,mRect.top+450);
		target->draw(ttt);

		t6.setString("SMS");
		t6.setOrigin(t6.getGlobalBounds().left + t6.getGlobalBounds().width/2.0f,t6.getGlobalBounds().top + t6.getGlobalBounds().height/2.0f);
		t6.setPosition(mRect.left+mRect.width/2,mRect.top+550);
		target->draw(t6);

		tttt.setString("EXIT GAME");
		tttt.setOrigin(tttt.getGlobalBounds().left + tttt.getGlobalBounds().width/2.0f,tttt.getGlobalBounds().top + tttt.getGlobalBounds().height/2.0f);
		tttt.setPosition(mRect.left+mRect.width/2,mRect.top+650);
		target->draw(tttt);

		t5.setString("<                    >");
		t5.setOrigin(t5.getGlobalBounds().left + t5.getGlobalBounds().width/2.0f,t5.getGlobalBounds().top + t5.getGlobalBounds().height/2.0f);
		t5.setPosition(mRect.left+mRect.width/2,mRect.top+250+100*mActiveAppID);
		target->draw(t5);*/

		if(!snakes)
		{
			rs.setTexture(mLines);
			target.draw(rs);
		}else if(s->getRender())
		{
			rs.setTexture(mLines);
			target.draw(rs);
			target.display();
			if(!s->gameOVER())
				s->setRender(false);
		}



		//if(mLoad || mSave)
		//{
		//	sf::Font f;
		//	f.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf");
		//	sf::Text t;
		//	t.setColor(sf::Color::White);
		//	t.setCharacterSize(20);
		//	t.setFont(f);
		//	t.setPosition(mRect.left+mApp[7].left-200,mRect.top+mApp[7].top-100);
		//	t.setString(mSL->loadText(0));
		//	target->draw(t);

		//	t.setPosition(mRect.left+mApp[8].left-200,mRect.top+mApp[8].top-50);
		//	t.setString(mSL->loadText(1));
		//	target->draw(t);

		//	t.setPosition(mRect.left+mApp[9].left-200,mRect.top+mApp[9].top-30);
		//	t.setString(mSL->loadText(2));
		//	target->draw(t);
		//}


		/*sf::RectangleShape rss;
		rss.setPosition(mRect.left+mApp[mActiveAppID].left,mRect.top+mApp[mActiveAppID].top);
		rss.setSize(sf::Vector2f(10,10));
		rss.setFillColor(sf::Color::Green);
		target->draw(rss);*/
	}
}