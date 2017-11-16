#pragma once
class Player : public Entity
{
public: // Methods
	Player(sf::Vector2f initPosition);

	int MaxBullets = 10;
	std::vector<std::unique_ptr<Bullet>>	Bullets;

	void									draw(sf::RenderWindow& window);
	void									update(sf::Time dt);
	void									move(sf::Vector2f distance);
	void									handelMovement(sf::Time& dt);
	const EntityBounds						getEntityBounds();

private: // Methods
	void									fireBullet();

private: // Data Members
	sf::CircleShape							mRoller;
	bool									mIsMovingDown;
	bool									mIsFacingRight;
};