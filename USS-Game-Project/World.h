#pragma once
#include "ResourceIdentifiers.h"
class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw();


private:

	enum class Collision {
		Left,
		Right,
		Bottom
	};
	
	void								loadTextures();
	void								buildScene();
	void								checkCollisions(Collision direction);
	void								createPlatform(sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::White);
	void								spawnEnemy();

private:
	Player								mFirstPlayer;
	sf::RenderWindow&					mWindow;
	TextureHolder						mTextures;
	std::vector<RectPointer>			mPlatforms;
	std::vector<Enemy>					mEnemies;
	static int							MaxEnemies;
};