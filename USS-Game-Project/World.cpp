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
	for (int i = 0; i < mPlatforms.size(); i++) {
		if (mFirstPlayer.isFalling()) {
			sf::Vector2f platformPosition = mPlatforms[i].get()->getPosition();
			sf::Vector2f platformSize = mPlatforms[i].get()->getSize();
			sf::Vector2f playerBound = mFirstPlayer.getLoverBound();
			if (
				playerBound.x > platformPosition.x &&
				playerBound.y > platformPosition.y &&
				playerBound.x < platformPosition.x + platformSize.x &&
				playerBound.y < platformPosition.y + platformSize.y
				) {
				mFirstPlayer.setOnPlatform(true);
			}
		}
	}
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
	RectPointer r = RectPointer(new sf::RectangleShape({ 1366, 30 }));
	Platform p;
	r->setPosition(0, 668);
	p.set(std::move(r));
	mPlatforms.push_back(p.get());
}