#pragma once
class Bullet
{
public:
	Bullet(bool isFiredTowardsRight);
	void				draw(sf::RenderWindow& window);
	void				setPosition(sf::Vector2f position);
	sf::Vector2f		getPosition();

private:
	sf::RectangleShape  mBullet;
	bool				mIsFiredTowardsRight;
};

