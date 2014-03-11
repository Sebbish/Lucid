#include "Button.h"


Button::Button(sf::Texture* texture):
	mTexture(texture)
{
}


Button::~Button(void)
{
}

void Button::setObject(Object* object)
{
	mObject = object;
}

void Button::willRender(bool render)
{
	mWillRender = render;
}

bool Button::getRender()
{
	return mWillRender;
}

void Button::render(sf::RenderWindow* window, Camera* camera)
{
	if (mObject != 0)
	{
		if (mWillRender)
		{
			sf::RectangleShape r;
			r.setTexture(mTexture);
			float temp = mClock.getElapsedTime().asSeconds();
			r.setTextureRect(sf::IntRect(64*((int)temp % 2), 0, 64, 64));
			r.setPosition(mObject->getRect().left + 96 - camera->getView()->getCenter().x + (camera->getView()->getSize().x / 2), mObject->getRect().top + 32 - camera->getView()->getCenter().y + (camera->getView()->getSize().y / 2));
			r.setSize(sf::Vector2f(64, 64));
			window->draw(r);
		}
	}
}