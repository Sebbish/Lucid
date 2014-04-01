#ifndef DEEPBLUE_LIGHT_H
#define DEEPBLUE_LIGHT_H

namespace sf
{
	class Texture;
	class RenderTexture;
}

#include "SFML\Graphics.hpp"
#include <SFML\System\Vector2.hpp>

namespace db 
{
	class Light
	{
		
	public:
		enum direction {
		LEFT,
		RIGHT
		};
		// Initializes the light.
		// @param texture: Masking texture for the light.
		// @param position: Position of where to draw the light.
		// @param color: Color of the light, alpha is intensity.
		// @param addBlend: Draw light with addaptive blending or not.
		Light( sf::Texture& texture, int typID, sf::Vector2f& position, float width, float height, sf::Color& color, float anitmationPicX, float animationPicY, float onOff, float playerBased, float blink, bool addBlend = true);

		// Renders the light.
		// @param target: The texture of which to render onto.
		void render( sf::RenderTexture& target );

		// Retrives the light position.
		// @return: A vector containing position, expressed in float.
		sf::Vector2f getPosition() const;

		// Retrives the color of the light.
		// @return: Color of the light, alpha is intensity.
		sf::Color getColor() const;

		// Sets the position of the light.
		// @param position: A vector containing position, expressed in float.
		void setPosition( sf::Vector2f& position );

		// Retrives the color of the light.
		// @param color: Color of the light, alpha is intensity.
		void setColor( sf::Color& color );

		void flipSprite(int direction);

		void setOnOff(bool onOff);

		void setMoveOnOff(bool moveOnOff);

		bool getOnOff();

		void setScale(float x, float y);

		void tick();

		int getXSize();

		void setBlink(bool blinka);

		void setWorldLight(int ambianceRed, int ambianceGreen, int ambianceBlue);

		int getWorldLightRed();
		int getWorldLightGreen();
		int getWorldLightBlue();

	private:
		sf::Sprite mSprite;
		sf::Color mColor;
		sf::Clock* mBlinkTimer;
		sf::FloatRect mRect;
		//const sf::IntRect &mIntRect;
		direction mDirection;
		float mScaleX;
		float mScaleY;
		float mAnimationPicX;
		float mAnimationPicY;
		float mAnimationTimer;
		float mAnimationSpeed;
		bool mAddBlend;
		bool mOnOff;
		bool mMoveOnOff;
		bool mPlayerBased;
		bool mBlink;
		//int mBlinkTimer;
		int mAbianceRed;
		int mAbianceGreen;
		int mAbianceBlue;
		int mTypeID;
		
		bool mBlinkStart;
		int mBlinkTimerStart;
	};
}


#endif