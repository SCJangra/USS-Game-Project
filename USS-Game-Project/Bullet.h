#pragma once
class Bullet
{
public:
	Bullet(bool isFiredTowardsRight);
	void				update(sf::Time& dt);
	void				draw(sf::RenderWindow& window);
	void				setPosition(sf::Vector2f position);
	sf::Vector2f		getPosition();
	sf::Vector2f		getSize();
	void				setTexture(sf::Texture& texture);
private:
	sf::RectangleShape  mBullet;
	bool				mIsFiredTowardsRight;
};