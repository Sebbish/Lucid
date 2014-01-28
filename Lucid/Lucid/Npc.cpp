#include "Npc.h"

Npc::Npc(sf::Vector2f position, sf::Vector2f size, int dialogueID):
	mPosition(position), mSize(size), mDialogueID(dialogueID)
{
}

Npc::~Npc()
{
}

sf::Vector2f Npc::getPosition()const
{
	return mPosition;
}

sf::Vector2f Npc::getSize()const
{
	return mSize;
}

int Npc::getDialogueID()
{
	return mDialogueID;
}