#include "stdafx.h"
#include "World.h"

int World::MaxEnemies = 20;

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mTextures()
	, mFirstPlayer({ 200, 200 })
	, mPlatforms()
	, mEnemies()
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	checkCollisions(Collision::Left);
	checkCollisions(Collision::Right);
	checkCollisions(Collision::Bottom);
	mFirstPlayer.update(dt);

	spawnEnemy();
	for (int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i].calculateCollisions(mPlatforms);
		mEnemies[i].update(dt);
		if (mEnemies[i].getBody().getPosition().y > 768) {
			mEnemies.erase(mEnemies.begin() + i);
		}
	}
}

void World::draw()
{
	mFirstPlayer.draw(mWindow);

	for (int i = 0; i < mPlatforms.size(); i++) {
		mWindow.draw(*mPlatforms[i].get());
	}
	for (int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i].draw(mWindow);
	}
}

void World::loadTextures()
{
}

void World::buildScene()
{
	float height = 30.f; int dis = 10;
	createPlatform({ 340,height }, { 0, 738 });
	createPlatform({ 346, height }, {510 , 738 });
	createPlatform({ 340, height }, { 1026 , 738 });
	createPlatform({ 30, 738 }, { 0, 0 }); 
	createPlatform({ 30,738 }, { 1336,0 }); 

	createPlatform({ 450,15}, { 70,608 });//level
	createPlatform({ 150,15 }, { 600,608 });
	createPlatform({ 375,15 }, { 900,608 });
	createPlatform({ 200,15}, { 90,473 });
	createPlatform({ 300,15 }, { 380,473 });
	createPlatform({ 350,15 }, { 856,473});
	createPlatform({ 175,15 }, { 30,338 });
	createPlatform({ 300,15 }, { 350,338 });
	createPlatform({ 250,15 }, { 750,338 });
	createPlatform({ 140,15 }, { 1196,338 });
	createPlatform({ 350,15 }, { 160,203 });
	createPlatform({ 100,15 }, { 683,203 });
	createPlatform({ 350,15 }, { 900,203 });

}

void World::checkCollisions(Collision direction)
{
	sf::Vector2f playerBound;
	switch (direction) {
	case Collision::Left:
		playerBound = mFirstPlayer.getLeftBound();
		break;
	case Collision::Right:
		playerBound = mFirstPlayer.getRightBound();
		break;
	case Collision::Bottom:
		playerBound = mFirstPlayer.getLoverBound();
	}

	for (int i = 0; i < mPlatforms.size(); i++) {
		if (mFirstPlayer.isFalling()) {
			sf::Vector2f platformPosition = mPlatforms[i].get()->getPosition();
			sf::Vector2f platformSize = mPlatforms[i].get()->getSize();
			if (
				playerBound.x + 2 >= platformPosition.x &&
				playerBound.y + 2 >= platformPosition.y &&
				playerBound.x - 2 <= platformPosition.x + platformSize.x &&
				playerBound.y - 2 <= platformPosition.y + platformSize.y
				) {
				switch (direction) {
				case Collision::Left:
					mFirstPlayer.leftContact = true;
					break;
				case Collision::Right:
					mFirstPlayer.rightContact = true;
					break;
				case Collision::Bottom:
					mFirstPlayer.bottomContact = true;
					break;
				}
			}
		}
	}
}

void World::createPlatform(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	RectPointer rect(new sf::RectangleShape(size));
	rect->setPosition(position);
	rect->setFillColor(color);

	mPlatforms.push_back(std::move(rect));
}

void World::spawnEnemy()
{
	static sf::Clock clock;
	if (clock.getElapsedTime() > sf::seconds(1.f) && mEnemies.size() < MaxEnemies) {
		mEnemies.push_back(Enemy());
		clock.restart();
	}
}