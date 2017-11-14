#include "stdafx.h"
#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mTextures()
	, mFirstPlayer({ 200, 200 })
	, mPlatforms()
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	mFirstPlayer.update(dt);
}

void World::draw()
{
	mFirstPlayer.draw(mWindow);

	for (int i = 0; i < mPlatforms.size(); i++) {
		mWindow.draw(*mPlatforms[i].get());
	}
}

void World::loadTextures()
{
}

void World::buildScene()
{
	RectPointer rect(new sf::RectangleShape({ 1366, 30 }));
	rect->setPosition({ 0, 668 });
	rect->setFillColor(sf::Color::White);

	mPlatforms.push_back(std::move(rect));
}