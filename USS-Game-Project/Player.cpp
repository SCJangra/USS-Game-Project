#include "stdafx.h"
#include "Player.h"

const float Player::MovementSpeed = 500.f;

Player::Player(sf::Vector2f initPosition)
	: Entity()
	, mIsMovingDown(false)
	, mIsFacingRight(true)
	, mBulletTextureLeft()
	, mBulletTextureRight()
	, mBulletBuffer()
	, mBulletSound()
	, mClock()
	, mPlayerTextureLeft()
	, mPlayerTextureRight()
{
	mPlayerTextureLeft.loadFromFile("Assets/Textures/Player/PlayerLeft.png");
	mPlayerTextureRight.loadFromFile("Assets/Textures/Player/PlayerRight.png");

	// Load Bullet textures
	mBulletTextureLeft.loadFromFile("Assets/Textures/Bullets/Bullet1Left.png");
	mBulletTextureRight.loadFromFile("Assets/Textures/Bullets/Bullet1Right.png");

	// Initialize Player Body size and position
	mBody.setSize({ 70, 70 });
	mBody.setPosition({ initPosition.x, initPosition.y });
	mBody.setTexture(&mPlayerTextureRight);

	mBulletBuffer.loadFromFile("Assets/Music/BulletFire/BulletFire.wav");
	mBulletSound.setBuffer(mBulletBuffer);
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(mBody);

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

	mBottomContact = false;
	mRightContact = false;
	mLeftContact = false;
}

void Player::update(sf::Time dt)
{
	handelMovement(dt);

	// Check if fire key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		fireBullet();
	}
	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i]->update(dt);
	}
}

void Player::handelMovement(sf::Time& dt)
{
	sf::Vector2f movement(0.f, 0.f);
	bool keyPressed_W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool keyPressed_S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool keyPressed_A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool keyPressed_D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (mBody.getPosition().y <= 0) mTopContact = true;

	if (keyPressed_W && !mTopContact) {
		movement.y -= MovementSpeed;
		mIsMovingDown = false;
	}
	if (keyPressed_S)					movement.y += MovementSpeed;
	if (keyPressed_A && !mLeftContact) {
		movement.x -= MovementSpeed;
		mIsFacingRight = false;
		mBody.setTexture(&mPlayerTextureLeft);
	}
	if (!keyPressed_A && mLeftContact)	movement.x += MovementSpeed;
	if (keyPressed_D && !mRightContact) {
		movement.x += MovementSpeed;
		mIsFacingRight = true;
		mBody.setTexture(&mPlayerTextureRight);
	}
	if (!keyPressed_D && mRightContact) movement.x -= MovementSpeed;

	if (!keyPressed_W && !mBottomContact) {
		movement.y += MovementSpeed;
		mIsMovingDown = true;
	}
	
	move(movement * dt.asSeconds());
}

const Entity::EntityBounds Player::getEntityBounds()
{
	EntityBounds bounds;
	bounds.position = mBody.getPosition();
	bounds.size = mBody.getSize();

	return bounds;
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
				mBody.getPosition().y + mBody.getSize().y / 2.5f });
			bullet->setTexture(mBulletTextureRight);
		}
		else
		{
			bullet->setPosition({
				mBody.getPosition().x - 75,
				mBody.getPosition().y + mBody.getSize().y / 2.5f });
			bullet->setTexture(mBulletTextureLeft);
		}
		Bullets.push_back(std::move(bullet));
		mBulletSound.play();

		mClock.restart();
	}
}