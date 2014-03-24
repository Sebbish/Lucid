#include "Mobil.h"


Mobil::Mobil(sf::Texture* texture,sf::Texture* lines,int mapID,sf::Texture* Voicemail,sf::Vector2u windowSize):
	mTexture(texture),mLines(lines),mActivated(false)
{

	mRect.height = windowSize.y;
	mRect.width = (float)windowSize.y*((float)mTexture->getSize().x/(float)mTexture->getSize().y);

	snakes = false;
	mVM = new VoiceMail(mapID,Voicemail);
	mVoiceMail = false;
	slutPÂTest = false;
	f.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf");
	//f.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf");

	getMC = false;
	rs.setPosition(mRect.left,mRect.top);
	rs.setSize(sf::Vector2f(mRect.width,mRect.height));
	rs.setTexture(mTexture);
	t.setColor(sf::Color(0,0,0));
	t.setCharacterSize(60);
	t.setFont(f);
	t.setString("<                    >");
	t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2.0f,t.getGlobalBounds().top + t.getGlobalBounds().height/2.0f);
	t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*mVM->getActiveSoundID());
	while(t.getLocalBounds().width >= 750*(mRect.width/(float)mTexture->getSize().x))
	{
		t.setCharacterSize(t.getCharacterSize()-1);
		t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2.0f,t.getGlobalBounds().top + t.getGlobalBounds().height/2.0f);
		t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*mVM->getActiveSoundID());
	}
	mVoiceMail2 = false;
	mVD = new VoiceDialog(Voicemail);
	mVD->newLevel(mapID);
}



Mobil::~Mobil()
{
}


void Mobil::boatLvl8Thing()
{
	mVD->boatLvl8Thing();
}

//aktiverar mobilen och s‰tter r‰tt position
void Mobil::activate(sf::RenderWindow* view)
{
	mRect.left = view->getPosition().x+view->getSize().x/2-mRect.width/2;
	mRect.top = view->getPosition().y+view->getSize().y/2-mRect.height/2;
	rs.setPosition(mRect.left,mRect.top);
	mActivated = true;
	mActiveAppID = 0;
	textY = rs.getPosition().x,(250.0f/(float)mTexture->getSize().y)*mRect.height;
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
	mVM->activateNextSound(true);
}

void Mobil::nextDialog()
{
	mVD->playNextDialog();
}

//markerar n‰sta app
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

//markerar fˆregÂende app
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
			mActiveAppID = 0;
			return -1;
		}
		mVoiceMail2 = false;
		return mActiveAppID;
	}
	else if(mVoiceMail2 && mVoiceMail)
	{
		mVM->playSound(mVM->getActiveSoundID());
		return -1;
	}else
		mVoiceMail2 = true;
		
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

//retunerar om mobilen ‰r aktiv
bool Mobil::getActivate()const
{
	return mActivated;
}

void Mobil::newMap(int mapID)
{
	mVM->newMap(mapID);
	slutPÂTest = false;
	getMC = false;
	mVD->newLevel(mapID);
}

bool Mobil::playingLvl8Thing()
{
	return mVD->playingLvl8Thing();
}

int Mobil::getDialogID()
{
	return mVD->getDialogID();
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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mVoiceMail)
		mVoiceMail = false;
}

//renderar
void Mobil::render(sf::RenderWindow& target)
{

	if(mActivated)
	{
			
			rs.setTexture(mTexture);
			target.draw(rs);
	
			if(!snakes && !mVoiceMail)
			{

				t.setString("NEW GAME");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,textY-t.getLocalBounds().height*3);
				target.draw(t);
				firstMenuThing.x = t.getPosition().x;
				firstMenuThing.y = t.getPosition().y;
				textH = t.getGlobalBounds().height;

				t.setString("LOAD GAME");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,t.getPosition().y+t.getLocalBounds().height*2);
				target.draw(t);

				t.setString("VOICE MAIL");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,t.getPosition().y+t.getLocalBounds().height*2);
				target.draw(t);

				t.setString("EXIT GAME");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,t.getPosition().y+t.getLocalBounds().height*2);
				target.draw(t);

				t.setString("<                    >");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,firstMenuThing.y+mActiveAppID*(textH*2));
				target.draw(t);
			}else if(!snakes && mVoiceMail)
			{
			
				t.setString("VOICE MAIL");
				t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
				t.setPosition(mRect.left+mRect.width/2,mRect.top+250);
				target.draw(t);
				int j = 0;
				if(mVM->getSounds().size() > 0)
				{
					if(mVM->getActiveSoundID() <= 2)
					{
						for(int i = 0; i < 4;i++)
						{
							if(i+1 <= mVM->getSounds().size())
							{
							t.setString(mVM->getSounds()[i]->mTitle);
							t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
							t.setPosition(mRect.left+mRect.width/2,mRect.top+350+j*100);
							target.draw(t);
							}
							t.setString("<                           >");
							t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
							if(mVM->getActiveSoundID() < 0)
								t.setPosition(mRect.left+mRect.width/2,mRect.top+350);
							else
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

							t.setString("<                           >");
							t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
							t.setPosition(mRect.left+mRect.width/2,mRect.top+355+100*3);
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

							t.setString("<                           >");
							t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width/2.0f,t.getLocalBounds().top + t.getLocalBounds().height/2.0f);
							t.setPosition(mRect.left+mRect.width/2,mRect.top+350+100*2);
							target.draw(t);
							j++;
						}
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
}



void Mobil::VoiceMailTick()
{
	mVM->tick();
	mVD->tick();
}

void Mobil::VoiceMailRender(sf::RenderWindow *target)
{
	mVM->render(target);
	mVD->render(target);
	if(slutPÂTest)
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

void Mobil::setCurrentLevel(int LVL)
{
	mcurrentLevel = LVL;
}

int Mobil::getCurrentLevel()
{
	return mcurrentLevel;
}