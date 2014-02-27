#include "snake.h"


snake::snake(sf::FloatRect &rect):
	mRect(rect)
{
	t.loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/kladd.png");
	l.loadFromFile("P:/Downloads/LucidProject/Resources/Graphics/Animations/l_snake.png");
	mRect.left += 160;
	mRect.top += 200;
	mRect.width = 720;
	mRect.height = 520;
	init();
	mMusic.openFromFile("P:/Downloads/LucidProject/Resources/Music/Lucid Chiptuna 01.ogg");
	mMusic.setLoop(true);
	mMusic.play();
}


snake::~snake()
{
	while(cubes.size() > 0)
	{
		delete cubes[cubes.size()-1];
		cubes.pop_back();
	}
}

void snake::exit()
{
	mState = EXIT;
}

void snake::init()
{
	srand(time(NULL));
	mTime = 1000/10;
	mState = GAME;
	mScore = 0;
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+80,mRect.top+90,40,40),true,false,t,mRect));
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+40,mRect.top+90,40,40),false,false,t,mRect));
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+0,mRect.top+90,40,40),false,false,t,mRect));
	mFruit = new Cube(sf::FloatRect(mRect.left+((rand() % (680))/30)*30,mRect.top+((rand() % (490))/30)*30,10,62),false,true,l,mRect);
	
	mFont.loadFromFile("BuxtonSketch.ttf");
	mText.setFont(mFont);
	mText.setPosition(mRect.left,mRect.top);
	mText.setCharacterSize(32);
	mText.setColor(sf::Color::Black);
	mRender = true;
	
}



bool snake::exitPls()const
{
	if(mState == EXIT)
		return true;
	
	return false;
}

bool snake::gameOVER()const
{
	if(mState == OVER)
		return true;

	return false;
}

void snake::spawnNewFruit()
{
	sf::FloatRect rect(mRect.left+((rand() % (680))/30)*30,mRect.top+((rand() % (490))/30)*30,10,49);
	mFruit->setRect(rect);
	if(snakeCollideWithFruit())
		spawnNewFruit();
}

void snake::collide()
{
	if(snakeCollideWithFruit())
	{
		cubes.push_back(new Cube(cubes[cubes.size()-1]->getRect(),false,false,t,mRect));
		spawnNewFruit();
		mScore += 100;
	}
	if(snakeCollideWithSnake())
		mState = OVER;
}

bool snake::snakeCollideWithFruit()
{
	for(auto i:cubes)
	{
		if(mFruit->getRect().intersects(i->getRect()))
			return true;
	}
	return false;
}

bool snake::snakeCollideWithSnake()
{
	for(auto i:cubes)
	{
		if(cubes[0] != i)
			if(cubes[0]->getRect().intersects(i->getRect()))
				return true;
	}
	return false;
}

void snake::tick()
{

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	mState = EXIT;

	if(mState == GAME)
	{

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			cubes[0]->setDirection(Cube::RIGHT);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			cubes[0]->setDirection(Cube::LEFT);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			cubes[0]->setDirection(Cube::UP);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			cubes[0]->setDirection(Cube::DOWN);


	if(mClock.getElapsedTime().asMilliseconds() >= mTime)
	{

		for(int i = cubes.size()-1; i >= 0 ;i--)
			if(i > 0)
				cubes[i]->tick(cubes[i-1]->getRect());
			else
				cubes[i]->tick(cubes[i]->getRect());

		collide();

		mRender = true;
		mClock.restart();
	}
	}
	if(mState == OVER)
		mRender = true;
}

bool snake::getRender()const
{
	return mRender;
}

void snake::setRender(bool render)
{
	mRender = render;
}

void snake::render(sf::RenderWindow& target)
{
	if(mRender)
	{
	mFruit->render(target);
	for(auto i:cubes)
		i->render(target);

	mText.setOrigin(0,0);
	mText.setPosition(mRect.left,mRect.top);
	mText.setCharacterSize(32);
	mText.setString("SCORE: " + std::to_string(mScore));
	target.draw(mText);

	if(mState == OVER)
	{
		mText.setCharacterSize(72);
		mText.setString("GAME\nOVER");
		mText.setOrigin(mText.getLocalBounds().left+mText.getLocalBounds().height/2.0f,mText.getLocalBounds().top+mText.getLocalBounds().width/2.0f);
		mText.setPosition(mRect.left+mRect.width/2,mRect.top+mRect.height/2);
		target.draw(mText);
	}

	}


}
