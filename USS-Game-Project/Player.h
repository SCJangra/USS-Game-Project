#pragma once
class Player
{
public:
	Player(sf::Vector2f initPosition);

	void						draw(sf::RenderWindow& window);
	void						update(sf::Time dt);

	bool						isOnPlatform();
	void						setOnPlatform(bool onPlatform);

	const sf::Vector2f			getLoverBound();

	bool						isFalling();

	~Player();

private:
	void						move(sf::Vector2f distance);
	void						handelInput(sf::Time dt);

private:
	sf::Vector2f				mMovement;
	sf::RectangleShape			mBody;
	sf::CircleShape				mRoller;

	bool						mIsMovingUp;
	bool						mIsMovingDown;
	bool						mIsMovingRight;
	bool						mIsMovingLeft;
	bool						mIsOnPlatform;

	static const float			MovementSpeed;
};