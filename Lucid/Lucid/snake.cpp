#include "snake.h"


snake::snake(sf::FloatRect &rect):
	mRect(rect)
{
	mSnakeTexture.loadFromFile("../../../LucidProject/Resources/Graphics/Animations/kladd.png");
	mLewisTexture.loadFromFile("../../../LucidProject/Resources/Graphics/Animations/l_snake.png");
	mRect.left += 155;
	mRect.top += 205;
	mRect.width = 720;
	mRect.height = 520;
	init();
	mMusic.openFromFile("../../../LucidProject/Resources/Music/Lucid Chiptuna 01.ogg");
	mMusic.setLoop(true);
	mMusic.play();
	mBorder[0] = sf::Vector2f(mRect.left,mRect.top);
	mBorder[1] = sf::Vector2f(mRect.left+mRect.width,mRect.top);
	mBorder[2] = sf::Vector2f(mRect.left+mRect.width,mRect.top);
	mBorder[3] = sf::Vector2f(mRect.left+mRect.width,mRect.top+mRect.height);
	mBorder[4] = sf::Vector2f(mRect.left+mRect.width,mRect.top+mRect.height);
	mBorder[5] = sf::Vector2f(mRect.left,mRect.top+mRect.height);
	mBorder[6] = sf::Vector2f(mRect.left,mRect.top+mRect.height);
	mBorder[7] = sf::Vector2f(mRect.left,mRect.top);
	for(int i = 0; i < 8; i++)
		mBorder[i].color = sf::Color::Black;
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
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+80,mRect.top+90,40,40),true,false,mSnakeTexture,mRect));
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+40,mRect.top+90,40,40),false,false,mSnakeTexture,mRect));
	cubes.push_back(new Cube(sf::FloatRect(mRect.left+0,mRect.top+90,40,40),false,false,mSnakeTexture,mRect));
	mFruit = new Cube(sf::FloatRect(mRect.left+((rand() % (680))/40)*40,mRect.top+((rand() % (490))/40)*40,10,40),false,true,mLewisTexture,mRect);
	
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
	sf::FloatRect rect(mRect.left+((rand() % (680))/40)*40,mRect.top+((rand() % (490))/40)*40,10,40);
	mFruit->setRect(rect);
	if(snakeCollideWithFruit())
		spawnNewFruit();
}

void snake::collide()
{
	if(snakeCollideWithFruit())
	{
		cubes.push_back(new Cube(cubes[cubes.size()-1]->getRect(),false,false,mSnakeTexture,mRect));
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
		target.draw(mBorder,8,sf::Lines);
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
