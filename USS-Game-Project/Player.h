#pragma once
class Player : public Entity
{
public:		// Public Functions
	Player(sf::Vector2f initPosition);

	void									draw(sf::RenderWindow& window);
	void									update(sf::Time dt);
	void									move(sf::Vector2f distance);
	void									handelMovement(sf::Time& dt);
	const EntityBounds						getEntityBounds();

public:		// Public Data
	int MaxBullets = 10;
	std::vector<std::unique_ptr<Bullet>>	Bullets;
	static const float						MovementSpeed;

private:	// Private Functions
	void									fireBullet();

private:	// Private Data
	sf::SoundBuffer							mBulletBuffer;
	sf::Sound								mBulletSound;
	sf::Texture								mBulletTextureLeft;
	sf::Texture								mBulletTextureRight;
	bool									mIsMovingDown;
	bool									mIsFacingRight;

	sf::Clock								mClock;
	sf::Texture								mPlayerTextureLeft;
	sf::Texture								mPlayerTextureRight;
};