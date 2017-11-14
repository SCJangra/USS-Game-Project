#pragma once
#include "ResourceIdentifiers.h"
class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw();


private:
	void								loadTextures();
	void								buildScene();

private:
	Player								mFirstPlayer;
	sf::RenderWindow&					mWindow;
	TextureHolder						mTextures;
	std::vector<std::unique_ptr<sf::RectangleShape>>				mPlatforms;
};