#ifndef NPC_H
#define NPC_H

#include "object.h"
#include "Dialog.h"

class Npc :
	public Object
{
public:
	Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID,int animationPicX,Dialog* dialog,Entity* player,sf::SoundBuffer* idleSound,bool dialogActive);
	~Npc();
	int getDialogueID();
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual bool getShowE();
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
private:
	int mDialogueID;
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	int mAnimationPicX;
	float mAnimationSpeed;
	float mCurrentAnimationPic;
	Dialog* mDialog;
	bool mLookLeft;
	bool mChatting;
	Entity* mPlayer;
	sf::Sound mIdleSound;
	std::string mDialogFile;//endast namnet på filen utan .txt
	bool dialogActive;
	sf::RectangleShape r;
};

#endif