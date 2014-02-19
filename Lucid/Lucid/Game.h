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
#include "Effects.h"
#include "Dialog.h"
#include "Event.h"
#include "SaveLoad.h"
#include "LightManager.h"
#include "Flashlight.h"
#include "Light.h"
#include "Mobil.h"
#include "ambiance.h"

typedef std::vector<Entity*> EntiyVector;
typedef std::vector<Object*> ObjectVector;
typedef std::vector<db::Light*> LightVector;
typedef std::vector<LightSource*> LightSourceVector;

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
	void addLights();
	static bool overlapsEntity(Entity *playerEntity, Entity *otherEntity);
	static bool overlapsObjects(Entity *playerEntity, Object *objectEntity);
	static bool overlapsMouse(Entity *entity);
	void mousePositionFunc();
	sf::RenderWindow mWindow;
	sf::Vector2i mMousePosition;
	db::LightManager *lm;
	EntiyVector mEntities;
	LightSourceVector mLightSources;
	LightVector mLights;
	Camera *camera;
	Mobil *mMobil;
	Map* mMap;
	FilHanterare* mFH;
	float angle;
	bool mIsEPressed,mIsQPressed,mIsMPressed;
	sf::Clock clock;
	sf::Shader mShader;
	sf::RenderTexture mRenderTexture;
	Entity *mControlledEntity;
	Effects *mEffects;
	sf::Sound mDeathSound;
	Dialog *mDialog;
	Event* mEvent;
	bool mVisualizeValues;
	SaveLoad* mSL;
	int mAmbientRed;
	int mAmbientGreen;
	int mAmbientBlue;
	sf::Color testLight;
	bool mMenu;
	bool mMobilActivateApp();
	sf::Event event;
	ambiance *mAmbiance;
};

#endif