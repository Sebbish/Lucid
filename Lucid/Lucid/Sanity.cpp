#include "Sanity.h"


Sanity::Sanity():
	mSanity(100)
{
}


Sanity::~Sanity()
{
}

float Sanity::getSanity()const
{
	return mSanity;
}

void Sanity::setSanity(float sanity)
{
	mSanity += sanity;
}
