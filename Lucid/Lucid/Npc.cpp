#include "Npc.h"

Npc::Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID,int animationPicX,Dialog* dialog,Entity* player):
	mRect(rect), mDialogueID(dialogueID), mTexture(texture), mTypeID(typeID),mAnimationPicX(animationPicX),mAnimationSpeed(0.1f),mCurrentAnimationPic(0),mDialog(dialog),mLookLeft(true),mChatting(false),mPlayer(player)
{
	switch(mDialogueID)
	{
	case 0:
		mDialogFile = "Dialog";
		break;
	}
}

Npc::~Npc()
{
}

int Npc::getFunc(Entity* player)
{
	if(mDialog->getDraw())
	{
		mDialog->nextLine();
		mChatting = true;
	}else
	{
		mDialog->loadFile(mDialogFile);
		mChatting = true;
	}
	return 0;
}

sf::FloatRect Npc::getRect()const
{
	return mRect;
}

int Npc::getDialogueID()
{
	return mDialogueID;
}

void Npc::tick()
{
	if(mCurrentAnimationPic >= mAnimationPicX-0.1)
		mCurrentAnimationPic = 0;
	else
		mCurrentAnimationPic += mAnimationSpeed;
	if(mChatting && mTypeID != 4)
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