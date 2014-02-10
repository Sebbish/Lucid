#ifndef NPC_H
#define NPC_H

#include "object.h"

class Npc :
	public Object
{
public:
	Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID);
	~Npc();
	int getDialogueID();
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
private:
	int mDialogueID;
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
};

#endif