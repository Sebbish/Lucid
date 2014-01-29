#include "Npc.h"

Npc::Npc(sf::FloatRect rect, int dialogueID):
	mRect(rect), mDialogueID(dialogueID)
{
}

Npc::~Npc()
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