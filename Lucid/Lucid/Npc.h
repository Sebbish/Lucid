#ifndef NPC_H
#define NPC_H

#include "object.h"

class Npc :
	public Object
{
public:
	Npc(sf::Vector2f position, sf::Vector2f size, int dialogueID);
	~Npc();
	virtual sf::Vector2f getPosition()const;
	virtual sf::Vector2f getSize()const;
	int getDialogueID();
private:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	int mDialogueID;
};

#endif