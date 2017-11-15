#pragma once
class Player
{
public: // Methods
	Player(sf::Vector2f initPosition);

	void						draw(sf::RenderWindow& window);
	void						update(sf::Time dt);

	const sf::Vector2f			getLoverBound();
	const sf::Vector2f			getLeftBound();
	const sf::Vector2f			getRightBound();

	bool						isFalling();

public:  // Public Data
	bool						leftContact;
	bool						rightContact;
	bool						bottomContact;

private: // Functions or Methods
	void						move(sf::Vector2f distance);
	void						handelInput(sf::Time dt);

private: // Data Members
	sf::Vector2f				mMovement;
	sf::RectangleShape			mBody;
	sf::CircleShape				mRoller;

	bool						mIsMovingDown;

	static const float			MovementSpeed;
};