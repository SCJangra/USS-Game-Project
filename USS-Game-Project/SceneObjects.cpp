#include "stdafx.h"
#include "SceneObjects.h"


SceneObjects::SceneObjects()
{
}

void SceneObjects::setTexture(sf::Texture & texture)
{
	mTexture = texture;
}

void SceneObjects::draw(sf::RenderWindow & window)
{
	sprite.setTexture(mTexture);
	window.draw(sprite);
}
