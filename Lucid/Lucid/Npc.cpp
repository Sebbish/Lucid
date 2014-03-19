#include "Npc.h"

Npc::Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID,int animationPicX,Dialog* dialog,Entity* player,sf::SoundBuffer* idleSound,bool dialogActive):
	mRect(rect), mDialogueID(dialogueID), mTexture(texture), mTypeID(typeID),mAnimationPicX(animationPicX),mAnimationSpeed(0.08f),mCurrentAnimationPic(0),mDialog(dialog),mLookLeft(true),mChatting(false),mPlayer(player),dialogActive(dialogActive)
{
	mDialogFile = "Dialog"+std::to_string(mDialogueID);
	//mIdleSound.setBuffer(*idleSound);
	mIdleSound.setVolume(10);
	mIdleSound.setMinDistance(768);
	mIdleSound.setAttenuation(10);
	if(typeID == 29)
	{
		mIdleSound.setVolume(30);
	}
}

Npc::~Npc()
{
}

bool Npc::getShowE()
{
	return dialogActive;
}


int Npc::getFunc(Entity* player)
{
	if(dialogActive)
		if(mDialog->getDraw())
		{
			mDialog->nextLine();
			mChatting = true;
		}else
		{
			mDialog->loadFile(mDialogFile,mDialogueID);
			mChatting = true;
		}
	return 0;
}

sf::FloatRect Npc::getRect()const
{
	return mRect;
}

sf::FloatRect Npc::getHitBox()const
{
	sf::FloatRect hitBoxRect = mRect;
	hitBoxRect.left += 125;
	hitBoxRect.top += 26;
	hitBoxRect.height = 230;
	hitBoxRect.width = 6;
	return mRect;
}

int Npc::getDialogueID()
{
	return mDialogueID;
}

void Npc::tick()
{
	if(mPlayer->getRect().top+100 >= mRect.top && mPlayer->getRect().top-100 <= mRect.top)
	{
		mIdleSound.setPosition(mRect.left-mPlayer->getRect().left,0,0);
	}else
	{
		mIdleSound.setPosition(mRect.left-mPlayer->getRect().left,9999999,0);
	}
	if(mCurrentAnimationPic >= mAnimationPicX-0.1)
	{
		mIdleSound.stop();
		mIdleSound.play();
		mCurrentAnimationPic = 0;
	}else
		mCurrentAnimationPic += mAnimationSpeed;
	if(mChatting && mTypeID != 29)
	{
		if(!mDialog->getDraw())
			mChatting = false;
		else
		{
		if(mPlayer->getRect().left <= mRect.left)
			mLookLeft = true;
		else
			mLookLeft = false;
		}
	}
	if(mChatting && !mPlayer->getRect().intersects(getHitBox()))
	{
		mChatting = false;
		mDialog->setDraw(false);
	}
}

void Npc::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	if(mLookLeft)
		r.setTextureRect(sf::IntRect(mRect.width*(int)mCurrentAnimationPic,0,mRect.width,mRect.height));
	else
		r.setTextureRect(sf::IntRect(mRect.width*((int)mCurrentAnimationPic+1),0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}