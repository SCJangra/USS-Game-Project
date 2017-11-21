#include "stdafx.h"
#include "World.h"

int World::MaxEnemies = 20;

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mPlayer({ 200, 100 })
	, mPlatforms()
	, mEnemies()
	, mTiles()
	, mBGSprite()
	, mBGTexture()
	, mObjects()
{
	// Load and setup background
	mBGTexture.loadFromFile("Assets/Textures/BG/BG.png");
	mBGTexture.setSmooth(true);
	mBGSprite.setTexture(mBGTexture);
	mBGSprite.setScale({ 1.09f, 1.21f });
	mBGSprite.setPosition({ 0, 0 });


	loadTextures();

	/*-----------------------------------
	  | SetUp the Level					|
	  -----------------------------------*/
	float tileHeight = 64.f, tileWidth = 64.f;
	float tileHeight2 = 46;
	float screenHeight = 1080, screenWidth = 1920;

	// Line One
	createPlatform({ -1 * tileWidth, screenHeight - tileHeight }, { 10 * tileWidth, tileHeight }, 5);
	createPlatform({ 9 * tileWidth, screenHeight - tileHeight }, { 1 * tileHeight, tileWidth }, 6);
	createPlatform({ 14 * tileWidth, screenHeight - tileHeight }, { 1 * tileHeight, tileWidth }, 4);
	createPlatform({ 15 * tileWidth, screenHeight - tileHeight }, { 1 * tileHeight, tileWidth }, 5);
	createPlatform({ 16 * tileWidth, screenHeight - tileHeight }, { 1 * tileHeight, tileWidth }, 6);
	createPlatform({ 20 * tileWidth, screenHeight - tileHeight }, { 1 * tileWidth, tileHeight }, 4);
	createPlatform({ 21 * tileWidth, screenHeight - tileHeight }, { 10 * tileHeight, tileWidth }, 5);

	// Line Two
	createPlatform({ -1 * tileHeight, screenHeight - tileHeight * 2 }, { 10 * tileWidth, tileHeight }, 5);
	createPlatform({ 9 * tileWidth, screenHeight - tileHeight * 2 }, { 1 * tileHeight, tileWidth }, 6);
	createPlatform({ 14 * tileWidth, screenHeight - tileHeight * 2 }, { 1 * tileWidth, tileHeight }, 1);
	createPlatform({ 15 * tileWidth, screenHeight - tileHeight * 2 }, { 1 * tileWidth, tileHeight }, 2);
	createPlatform({ 16 * tileWidth, screenHeight - tileHeight * 2 }, { 1 * tileWidth, tileHeight }, 3);
	createPlatform({ 20 * tileWidth, screenHeight - tileHeight * 2}, { 1 * tileWidth, tileHeight }, 4);
	createPlatform({ 21 * tileWidth, screenHeight - tileHeight * 2}, { 10 * tileHeight, tileWidth }, 5);


	// Line Three
	createPlatform({ -1 * tileHeight, screenHeight - tileHeight * 3 }, { 7 * tileWidth, tileHeight }, 5);
	createPlatform({ 6 * tileWidth, screenHeight - tileHeight * 3 }, { 1 * tileWidth, tileHeight }, 10);
	createPlatform({ 7 * tileWidth, screenHeight - tileHeight * 3 }, { 2 * tileWidth, tileHeight }, 2);
	createPlatform({ 9 * tileWidth, screenHeight - tileHeight * 3 }, { 1 * tileWidth, tileHeight }, 3);
	
	createPlatform({ 20 * tileWidth, screenHeight - tileHeight * 3 }, { 1 * tileWidth, tileHeight }, 1);
	createPlatform({ 21 * tileWidth, screenHeight - tileHeight * 3 }, { 10 * tileWidth, tileHeight }, 2);

	// Line Four
	createPlatform({ -1 * tileWidth, screenHeight - tileHeight * 4 }, { 7 * tileWidth, tileHeight }, 2);
	createPlatform({ 6 * tileWidth, screenHeight - tileHeight * 4 }, { 1 * tileWidth, tileHeight }, 3);
	createPlatform({ 12.5f * tileWidth, screenHeight - tileHeight * 4 }, { 4 * tileWidth, tileHeight2 }, 15);

	// Line Five
	
	// Line Six
	createPlatform({ 22 * tileWidth, screenHeight - tileHeight * 6 }, { 1 * tileWidth, tileHeight }, 1);
	createPlatform({ 23 * tileWidth, screenHeight - tileHeight * 6 }, { 4 * tileWidth, tileHeight }, 2);
	createPlatform({ 27 * tileWidth, screenHeight - tileHeight * 6 }, { 1 * tileWidth, tileHeight }, 3);

	// Line Seven
	createPlatform({ 3 * tileWidth, screenHeight - tileHeight * 7 }, { 7 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 13 * tileWidth, screenHeight - tileHeight * 7 }, { 7 * tileWidth, tileHeight2 }, 15);

	// Line Eight
	

	// Line Ten
	createPlatform({ 4 * tileWidth, screenHeight - tileHeight * 10 }, { 9 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 15 * tileWidth, screenHeight - tileHeight * 10 }, { 2 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 19 * tileWidth, screenHeight - tileHeight * 10 }, { 5 * tileWidth, tileHeight2 }, 15);


	// Line Thirteen
	createPlatform({ -1 * tileWidth, screenHeight - tileHeight * 13 }, { 8 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 10 * tileWidth, screenHeight - tileHeight * 13 }, { 6 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 18 * tileWidth, screenHeight - tileHeight * 13 }, { 4 * tileWidth, tileHeight2 }, 15);
	createPlatform({ 24 * tileWidth, screenHeight - tileHeight * 13 }, { 8 * tileWidth, tileHeight2 }, 15);
}

void World::update(sf::Time& dt)
{
	mPlayer.calculateCollisions(mPlatforms);
	mPlayer.update(dt);

	spawnEnemy();
	for (int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->calculateCollisions(mPlatforms);
		mEnemies[i]->checkBulletHit(mPlayer.Bullets);
		mEnemies[i]->update(dt);
		if (mEnemies[i]->getEntityBounds().position.y > 1080) {
			mEnemies.erase(mEnemies.begin() + i);
			Game::Health--;
		}
		if (mEnemies[i]->HitCount >= 1) {
			mEnemies.erase(mEnemies.begin() + i);
			Game::Score++;
		}
	}
}

void World::draw()
{	
	mWindow.draw(mBGSprite);
	for (int i = 0; i < mObjects.size(); i++) {
		mObjects[i].draw(mWindow);
	}
	mPlayer.draw(mWindow);
	for (int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->draw(mWindow);
	}
	for (int i = 0; i < mPlatforms.size(); i++) {
		mWindow.draw(*mPlatforms[i].get());
	}
	
}

void World::createPlatform(sf::Vector2f position, sf::Vector2f size, int textureNumber, int rotate)
{
	
	RectPointer rect(new sf::RectangleShape(size));
	
	rect->setTexture(&mTiles[textureNumber]);
	rect->setTextureRect(sf::IntRect(0, 0, (int)size.x * 2, (int)size.y * 2));
	rect->setPosition(position);
	mPlatforms.push_back(std::move(rect));
}

void World::spawnEnemy()
{
	static sf::Clock clock;
	static sf::Clock speedClock;
	static float spawnSpeed = 1.f;
	if (clock.getElapsedTime() > sf::seconds(spawnSpeed) && mEnemies.size() < MaxEnemies) {
		mEnemies.push_back(std::make_unique<Enemy>());
		clock.restart();
	}

	// Increase enemy speed every two seconds
	if (speedClock.getElapsedTime() > sf::seconds(5.f)) {
		Enemy::MovementSpeed += 5;
		spawnSpeed -= .01f;
		speedClock.restart();
	}
}

void World::loadTextures()
{

	sf::Texture texture;
	sf::Sprite sprite;
	SceneObjects object;
	float screenWidth = 1920, screenHeight = 1080;
	float tileWidth = 64, tileHeight = 64;

	// Push an empty texture for location ZERO
	// i.e mTiles[0] is an empty texture
	mTiles.push_back(sf::Texture());

	for (int i = 1; i <= 18; i++) {
		texture.loadFromFile("Assets/Textures/Tiles/" + std::to_string(i) + ".png");
		texture.setRepeated(true);
		texture.setSmooth(true);
		mTiles.push_back(texture);
	}

	texture.loadFromFile("Assets/Textures/Object/Igloo.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 25 * tileWidth, screenHeight - tileHeight * 14.5f });
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Tree_1.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 13 * tileWidth, screenHeight - tileHeight * 6.17f });
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Tree_1.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 5.5f * tileWidth, screenHeight - tileHeight * 9.17f });
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Tree_2.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 27 * tileWidth, screenHeight - tileHeight * 5 });
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/SnowMan.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 3 * tileWidth, screenHeight - tileHeight * 5.6f });
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Crate.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 24 * tileWidth, screenHeight - tileHeight * 6.8f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 3, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Crate.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 24.4f * tileWidth, screenHeight - tileHeight * 7.58f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 2, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Crate.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 24.8f * tileWidth, screenHeight - tileHeight * 8.26f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 1, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/Tree_2.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 14.5f * tileWidth, screenHeight - tileHeight * 9 });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 2, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/IceBox.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 6 * tileWidth, screenHeight - tileHeight * 7.8f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 2, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/IceBox.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 20.5f * tileWidth, screenHeight - tileHeight * 10.8f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 2, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	texture.loadFromFile("Assets/Textures/Object/IceBox.png");
	object.setTexture(texture);
	object.sprite.setPosition({ 20.9f * tileWidth, screenHeight - tileHeight * 11.53f });
	object.sprite.setTextureRect(sf::IntRect(0, 0, object.mTexture.getSize().x * 1, object.mTexture.getSize().y * 1));
	mObjects.push_back(object);

	for (int i = 0; i < mObjects.size(); i++) {
		mObjects[i].sprite.setScale({ .5, .5 });
	}
}