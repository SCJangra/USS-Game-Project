#pragma once
#include "ResourceIdentifiers.h"
class World : private sf::NonCopyable
{
public:
	World(sf::RenderWindow& window);
	void								update(sf::Time& dt);
	void								draw();


private:
	void								createPlatform(sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::White);
	void								spawnEnemy();
	void								loadTextures();

private:
	sf::Texture							mTexturePlatform;
	Player								mFirstPlayer;
	sf::RenderWindow&					mWindow;
	std::vector<RectPointer>			mPlatforms;
	std::vector<std::unique_ptr<Enemy>>	mEnemies;
	static int							MaxEnemies;
};