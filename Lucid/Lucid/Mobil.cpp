#include "Mobil.h"


Mobil::Mobil(sf::Texture* texture,sf::Texture* lines,int mapID,sf::Texture* Voicemail):
	mTexture(texture),mLines(lines),mActivated(false)
{

	mRect.width = mTexture->getSize().x;
	mRect.height = mTexture->getSize().y;
	snakes = false;
	mVM = new VoiceMail(mapID,Voicemail);
	mVoiceMail = false;
	slutPåTest = false;
	f.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf");

	getMC = false;
}



Mobil::~Mobil()
{
}



//aktiverar mobilen och sätter rätt position
void Mobil::activate(sf::RenderWindow* view)
{
	mRect.left = view->getPosition().x+view->getSize().x/2-mRect.width/2;
	mRect.top = view->getPosition().y+view->getSize().y/2-mRect.height/2;
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

void Mobil::nextSound()
{
	mVM->activateNextSound();
}

//markerar nästa app
void Mobil::nextApp()
{
	if(!mVoiceMail)		
	{
		if(mActiveAppID <= 2)
			mActiveAppID++;
		else
			mActiveAppID = 0;
	}else
	{
		mVM->nextPrevSoundSlot(true);
	}
	
}

//markerar föregående app
void Mobil::lastApp()
{
	if(!mVoiceMail)
	{
		if(mActiveAppID >= 1)
			mActiveAppID--;
		else
			mActiveAppID = 3;
	}else
	{
		mVM->nextPrevSoundSlot(false);
	}
	
}

//retunerar ID till den markerade appen, vissa aktiverar vissa saker i mobilen
int Mobil::getActiveAppID()
{
	if(!mVoiceMail)
	{
		if(mActiveAppID == 2)
		{
			mVoiceMail = true;
			return -1;
		}

		return mActiveAppID;
	}
	else
		return -1;
}

//resetar mobilen
void Mobil::reset()
{
	mActiveAppID = 0;
}


void Mobil::ActivateSnakes()
{
	s = new snake(mRect, false);
	snakes = true;
}

void Mobil::ActivateSnakesAI()
{
	s = new snake(mRect, true);
	snakes = true;
}

//retunerar om mobilen är aktiv
bool Mobil::getActivate()const
{
	return mActivated;
}

void Mobil::newMap(int mapID)
{
	mVM->newMap(mapID);
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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&  !snakes)
		ActivateSnakesAI();
	mVM->tick();
}

//renderar
void Mobil::render(sf::RenderWindow& target)
{
	if(mActivated)
	{
			sf::RectangleShape rs;
			rs.setPosition(mRect.left,mRect.top);
			rs.setSize(sf::Vector2f(mRect.width,mRect.height));
			rs.setTexture(mTexture);
			target.draw(rs);
	
			if(!snakes && !mVoiceMail)
			{
							
				sf::Text t;
				t.setColor(sf::Color(0,0,0));
				t.setCharacterSize(60);
				t.setFont(f);

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

				t.setString("EXIT GAME");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,mRect.top+550);
				target.draw(t);

				t.setString("<                    >");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,mRect.top+250+100*mActiveAppID);
				target.draw(t);
			}else if(!snakes && mVoiceMail)
			{
				sf::Text t;
				t.setColor(sf::Color(0,0,0));
				t.setCharacterSize(60);
				t.setFont(f);
			
				t.setString("VOICE MAIL");
				t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2.0f,t.getGlobalBounds().top + t.getGlobalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,mRect.top+250);
				target.draw(t);
				int j = 0;
				if(mVM->getActiveSoundID() <= 2)
				{
					
				for(int i = 0; i <= 3;i++)
				{
					if(i <= mVM->getSounds().size()-1)
					{
					t.setString(mVM->getSounds()[i]->mTitle);
					t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
					t.setPosition(mRect.left+mRect.width/2,mRect.top+350+j*100);
					target.draw(t);
					}
					t.setString("<                    >");
					t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
					t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*mVM->getActiveSoundID());
					target.draw(t);
					j++;
				}

				}else if(mVM->getActiveSoundID() == mVM->getSounds().size()-1)
				{
					for(int i = mVM->getActiveSoundID()-3; i < mVM->getSounds().size();i++)
					{
						t.setString(mVM->getSounds()[i]->mTitle);
						t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
						t.setPosition(mRect.left+mRect.width/2,mRect.top+350+j*100);
						target.draw(t);

						t.setString("<                    >");
						t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
						t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*3);
						target.draw(t);

						j++;
					}
				}else
				{
					for(int i = mVM->getActiveSoundID()-2; i < mVM->getActiveSoundID()+2;i++)
					{
						t.setString(mVM->getSounds()[i]->mTitle);
						t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
						t.setPosition(mRect.left+mRect.width/2,mRect.top+350+j*100);
						target.draw(t);

						t.setString("<                    >");
						t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
						t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*2);
						target.draw(t);
						j++;
					}
				}

			}else if(snakes)
			{
				s->render(target);
			}


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
		
	}
	mVM->render(&target);
}

void Mobil::VoiceMailTick()
{
	mVM->tick();
}

void Mobil::VoiceMailRender(sf::RenderWindow *target)
{
	mVM->render(target);
	if(slutPåTest)
	{
		sf::Text t;
		t.setFont(f);
		t.setCharacterSize(72);
		t.setColor(sf::Color::Red);
		t.setString("END OF THE TEST!!!!!");
		t.setOrigin(t.getGlobalBounds().left+t.getGlobalBounds().width/2.0,t.getGlobalBounds().top+t.getGlobalBounds().height/2.0);
		t.setPosition(target->getPosition().x+target->getSize().x/2.0,target->getPosition().y+target->getSize().y/2.0);
		target->draw(t);
	}
}