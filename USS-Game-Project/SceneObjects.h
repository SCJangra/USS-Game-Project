#pragma once
class SceneObjects
{
public:
	SceneObjects();
	void						setTexture(sf::Texture& texture);
	void						draw(sf::RenderWindow& window);
	
	sf::Sprite					sprite;

	sf::Texture					mTexture;
};

