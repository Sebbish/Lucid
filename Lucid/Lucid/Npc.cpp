#include "Npc.h"

Npc::Npc(sf::FloatRect rect, int dialogueID, sf::Texture* texture, int typeID):
	mRect(rect), mDialogueID(dialogueID), mTexture(texture), mTypeID(typeID)
{
}

Npc::~Npc()
{
}

int Npc::getFunc(Entity* player)
{
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
}

void Npc::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}