#pragma once
#include "ResourceIdentifiers.h"
class World : private sf::NonCopyable
{
public:
	World(sf::RenderWindow& window);
	void								update(sf::Time& dt);
	void								draw();


private:
	void								createPlatform(sf::Vector2f position, sf::Vector2f size, int textureNumter, int rotate = 0);
	void								spawnEnemy();
	void								loadTextures();

private:
	std::vector<sf::Texture>					mTiles;
	std::vector<SceneObjects>					mObjects;
	sf::Sprite									mBGSprite;
	sf::Texture									mBGTexture;
	Player										mFirstPlayer;
	Player										mSecondPlayer;
	sf::RenderWindow&							mWindow;
	std::vector<RectPointer>					mPlatforms;
	std::vector<std::unique_ptr<Enemy>>			mEnemies;
	static int									MaxEnemies;
};