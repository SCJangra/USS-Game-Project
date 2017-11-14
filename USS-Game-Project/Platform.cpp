#include "stdafx.h"
#include "Platform.h"

void Platform::set(RectPointer rect)
{
	rect.get()->setFillColor(sf::Color::White);
	mPlatform = std::move(rect);
}

RectPointer Platform::get()
{
	return std::move(mPlatform);
}
