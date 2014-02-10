#ifndef EFFECTS_H
#define EFFECTS_H
#include <SFML\Graphics.hpp>

class Effects
{
public:
	Effects(void);
	~Effects(void);
	void tick(sf::Clock clock);
	void setNextShader(int number);
	sf::Shader& getShader();
private:
	sf::Shader mShaderWave;
	sf::Shader mShaderBlur;
	sf::Shader mShaderEdge;
	sf::Shader mShaderEmpty;
	sf::Shader mShaderPixelate;
	int mCurrentShader;
	int mNextShader;
	int mPreviousShader;
	float mEdgeValue;
	float mMaxEdgeValue;
	float mEdgeValueAcceleration;
	void updateValues();
};

#endif