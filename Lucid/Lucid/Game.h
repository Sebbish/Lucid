#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include <fstream>
#include <string>
#include "FilHanterare.h"
#include "Map.h"

typedef std::vector<Entity*> EntiyVector;
typedef std::vector<Object*> ObjectVector;

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void setControlledEntity(Entity* entity);
	void tick();
	void render();
	void collision();
	void input(Entity* entity);
	void loadMap(std::string filename, int mapID);
	static bool overlapsEntity(Entity *playerEntity, Entity *otherEntity);
	static bool overlapsObjects(Entity *playerEntity, Object *objectEntity);
	static bool overlapsMouse(Entity *entity);
	void mousePositionFunc();
	sf::RenderWindow *mWindow;
	sf::Vector2i mMousePosition;
	EntiyVector mEntities;
	Camera *camera;
	Map* mMap;
	FilHanterare* mFH;
	float angle;
	bool mIsEPressed,mIsQPressed;
	sf::Clock clock;
	sf::Shader mShader;
	sf::RenderTexture mRenderTexture;
	Entity *mControlledEntity;
	sf::Sound mDeathSound;
};

#endif