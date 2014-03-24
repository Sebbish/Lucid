#pragma once
#include "SFML\Graphics.hpp"
class Sanity
{
public:
	Sanity(sf::Texture* brus);
	~Sanity();
	float getSanity()const;
	void setSanity(float sanity);
	void tick();
	void render(sf::RenderWindow* window);
	sf::Shader& getShader();
	void setBrus(bool brus);
	bool fadeIsDone();
	void die();
	void live();
	bool getWhiteFadeOut();
private:
	float mSanity;
	sf::Texture *mBrusTexture, *mDieTexture;
	sf::Shader mWaveShader;
	sf::Shader mEmptyShader;
	sf::Clock clock;
	float mBrusAlpha;
	float mAlpha;
	float mAlphaSpeed;
	bool mBrus;

	bool mWhiteFadeIn;
	bool mWhiteFadeOut;

	float mDieFade;
	float mBlurValue;
	bool mDie;
	int mDelayTimer;

	float mAnimationSpeed;
	float mAnimationTimer;
	float mWaveAmp;
	float mWaveAmpSpeed;
};

