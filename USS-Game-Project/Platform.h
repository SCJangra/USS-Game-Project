#pragma once
#include "ResourceIdentifiers.h"
class Platform
{
public:
	void		set(RectPointer rect);
	RectPointer get();
	
private:
	RectPointer			mPlatform;
};

