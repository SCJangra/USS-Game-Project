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

	static const float						MovementSpeed;

	void									setUpKey(sf::Keyboard::Key key);
	void									setDownKey(sf::Keyboard::Key key);
	void									setRightKey(sf::Keyboard::Key key);
	void									setLeftKey(sf::Keyboard::Key key);
	void									setFireKey(sf::Keyboard::Key key);

private: // Methods
	void									fireBullet();

private: // Data Members
	sf::SoundBuffer							mBulletBuffer;
	sf::Sound								mBulletSound;
	sf::Texture								mBulletTextureLeft;
	sf::Texture								mBulletTextureRight;
	sf::CircleShape							mRoller;
	bool									mIsMovingDown;
	bool									mIsFacingRight;

	sf::Clock								mClock;

	// Keys
	sf::Keyboard::Key						mUpKey;
	sf::Keyboard::Key						mDownKey;
	sf::Keyboard::Key						mRightKey;
	sf::Keyboard::Key						mLeftKey;
	sf::Keyboard::Key						mFireKey;
};