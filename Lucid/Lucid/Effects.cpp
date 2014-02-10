#include "Effects.h"


Effects::Effects(void)
{
	mShaderEdge.loadFromFile("P:/SFML-2.1/examples/shader/resources/edgeMod.frag",sf::Shader::Fragment);
	mShaderWave.loadFromFile("P:/SFML-2.1/examples/shader/resources/wave.vert",sf::Shader::Vertex);
	mShaderBlur.loadFromFile("P:/SFML-2.1/examples/shader/resources/blur.frag",sf::Shader::Fragment);
	mShaderPixelate.loadFromFile("P:/SFML-2.1/examples/shader/resources/pixelate.frag",sf::Shader::Fragment);

	mShaderEdge.setParameter("texture", sf::Shader::CurrentTexture);
	mShaderPixelate.setParameter("texture", sf::Shader::CurrentTexture);
	mCurrentShader = 0;
	mMaxEdgeValue = 0.05;
	mEdgeValueAcceleration = 0.05;
}


Effects::~Effects(void)
{
}

void Effects::updateValues()
{
	if (mPreviousShader != mNextShader) //Byta shader
	{
		if (mPreviousShader == mCurrentShader) //avsluta
		{
			if (mPreviousShader == 0)
			{
				mCurrentShader = mNextShader;
			}

			else if (mPreviousShader == 1)
			{
				mCurrentShader = mNextShader;
			}

			else if (mPreviousShader == 2)
			{
				mCurrentShader = mNextShader;
			}

			else if (mPreviousShader == 3) //Edge
			{
				if (mEdgeValue < 1)
				{
					mEdgeValue += mEdgeValueAcceleration;
				}

				else
				{
					mCurrentShader = mNextShader;
				}
			}

			else if (mPreviousShader == 4)
			{
				mCurrentShader = mNextShader;
			}

			else if (mPreviousShader == 5)
			{
				mCurrentShader = mNextShader;
			}
		}
		else if (mCurrentShader == mNextShader) //Starta
		{
			if (mNextShader == 3) //Edge
			{
				if (mEdgeValue > mMaxEdgeValue)
				{
					mEdgeValue -= mEdgeValueAcceleration;
				}
			}
		}
	}
}

void Effects::tick(sf::Clock clock)
{
	updateValues();

	mShaderEdge.setParameter("edge_threshold",  mEdgeValue);

	mShaderWave.setParameter("wave_phase", clock.getElapsedTime().asSeconds());
	mShaderWave.setParameter("wave_amplitude", 0.5 * 20, 0.5 * 40);

	mShaderBlur.setParameter("blur_radius", sin(clock.getElapsedTime().asSeconds()) * 0.004f);

	mShaderPixelate.setParameter("pixel_threshold", sin(clock.getElapsedTime().asSeconds()) / 150);

	//mShader.bind(&mShader);
}

void Effects::setNextShader(int number)
{
	if (number == 3)
	{
		mEdgeValue = 1;
	}
	mNextShader = number;
	mPreviousShader = mCurrentShader;
}

sf::Shader& Effects::getShader()
{
	if (mCurrentShader == 0)
	{
		return mShaderEmpty;
	}

	else if (mCurrentShader == 1)
	{
		return mShaderWave;
	}

	else if (mCurrentShader == 2)
	{
		return mShaderBlur;
	}

	else if (mCurrentShader == 3)
	{
		return mShaderEdge;
	}

	else if (mCurrentShader == 4)
	{
		return mShaderPixelate;
	}
}