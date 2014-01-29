#include "Npc.h"

Npc::Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID):
	mRect(rect), mDialogueID(dialogueID), mTexture(texture), mTypeID(typeID)
{
}

Npc::~Npc()
{
}

void Npc::getFunc()
{

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
}

void Npc::render(sf::RenderWindow* window)
{
}