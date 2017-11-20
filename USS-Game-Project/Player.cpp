#include "stdafx.h"
#include "Player.h"

const float Player::MovementSpeed = 300.f;

Player::Player(sf::Vector2f initPosition)
	: Entity()
	, mIsMovingDown(false)
	, mIsFacingRight(true)
	, mBulletTextureLeft()
	, mBulletTextureRight()
	, mBulletBuffer()
	, mBulletSound()
	, mUpKey()
	, mDownKey()
	, mRightKey()
	, mLeftKey()
	, mFireKey()
	, mClock()
{
	// Load Bullet textures
	mBulletTextureLeft.loadFromFile("Assets/Textures/Bullets/Bullet1Left.png");
	mBulletTextureRight.loadFromFile("Assets/Textures/Bullets/Bullet1Right.png");

	// Initialize Player Body size and position
	mBody.setSize({ 30, 50 });
	mBody.setPosition({ initPosition.x, initPosition.y });
	mBody.setFillColor(sf::Color::Green);

	// Initialize Player wheel size and position
	mRoller.setRadius(15.f);
	mRoller.setOrigin({ 15, 15 });
	mRoller.setFillColor(sf::Color::Yellow);
	mRoller.setPosition(initPosition.x + 15, initPosition.y + 50);

	mBulletBuffer.loadFromFile("Assets/Music/BulletFire/BulletFire.wav");
	mBulletSound.setBuffer(mBulletBuffer);

}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(mBody);
	window.draw(mRoller);

	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i]->draw(window);
		if (Bullets[i]->getPosition().x > 1920.f ||
			Bullets[i]->getPosition().x < 0
		) 
		{
			Bullets.erase(Bullets.begin() + i);
		}
	}
}

void Player::move(sf::Vector2f distance)
{
	mBody.move(distance);
	mRoller.move(distance);

	mBottomContact = false;
	mRightContact = false;
	mLeftContact = false;
}

void Player::update(sf::Time dt)
{
	handelMovement(dt);

	// Check if fire key is pressed
	
}

void Player::handelMovement(sf::Time& dt)
{
	sf::Vector2f movement(0.f, 0.f);
	bool keyPressed_W = sf::Keyboard::isKeyPressed(mUpKey);
	bool keyPressed_S = sf::Keyboard::isKeyPressed(mDownKey);
	bool keyPressed_A = sf::Keyboard::isKeyPressed(mLeftKey);
	bool keyPressed_D = sf::Keyboard::isKeyPressed(mRightKey);

	if (mBody.getPosition().y <= 0) mTopContact = true;

	if (keyPressed_W && !mTopContact) {
		movement.y -= MovementSpeed;
		mIsMovingDown = false;
	}
	if (keyPressed_S)					movement.y += MovementSpeed;
	if (keyPressed_A && !mLeftContact) {
		movement.x -= MovementSpeed;
		mIsFacingRight = false;
	}
	if (!keyPressed_A && mLeftContact)	movement.x += MovementSpeed;
	if (keyPressed_D && !mRightContact) {
		movement.x += MovementSpeed;
		mIsFacingRight = true;
	}
	if (!keyPressed_D && mRightContact) movement.x -= MovementSpeed;

	if (!keyPressed_W && !mBottomContact) {
		movement.y += MovementSpeed;
		mIsMovingDown = true;
	}

	if (sf::Keyboard::isKeyPressed(mFireKey)) {
		fireBullet();
	}
	
	move(movement * dt.asSeconds());
}

const Entity::EntityBounds Player::getEntityBounds()
{
	EntityBounds bounds;
	bounds.position = mBody.getPosition();
	bounds.size.x = mBody.getSize().x;
	bounds.size.y = mBody.getSize().y + mRoller.getRadius();
	return bounds;
}

void Player::setUpKey(sf::Keyboard::Key key)
{
	mUpKey = key;
}

void Player::setDownKey(sf::Keyboard::Key key)
{
	mDownKey = key;
}

void Player::setRightKey(sf::Keyboard::Key key)
{
	mRightKey = key;
}

void Player::setLeftKey(sf::Keyboard::Key key)
{
	mLeftKey = key;
}

void Player::setFireKey(sf::Keyboard::Key key)
{
	mFireKey = key;
}

void Player::fireBullet()
{
	if (mClock.getElapsedTime()	> sf::seconds(.2f) &&
		MaxBullets				> Bullets.size()
	) 
	{
		std::unique_ptr<Bullet> bullet(new Bullet(mIsFacingRight));
		if (mIsFacingRight) {
			bullet->setPosition({
				mBody.getPosition().x + mBody.getSize().x,
				mBody.getPosition().y + mBody.getSize().y / 2 });
			bullet->setTexture(mBulletTextureRight);
		}
		else
		{
			bullet->setPosition({
				mBody.getPosition().x - 75,
				mBody.getPosition().y + mBody.getSize().y / 2 });
			bullet->setTexture(mBulletTextureLeft);
		}
		Bullets.push_back(std::move(bullet));
		mBulletSound.play();

		mClock.restart();
	}
}