#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Vector2f initPosition)
	: Entity()
	, mIsMovingDown(false)
	, mIsFacingRight(true)
	, mBulletTextureLeft()
	, mBulletTextureRight()
{
	mBulletTextureLeft.loadFromFile("Assets/Textures/Bullets/Bullet1Left.png");
	mBulletTextureRight.loadFromFile("Assets/Textures/Bullets/Bullet1Right.png");


	mBody.setSize({ 30, 50 });
	mBody.setPosition({ initPosition.x, initPosition.y });
	mBody.setFillColor(sf::Color::Green);

	mRoller.setRadius(15.f);
	mRoller.setOrigin({ 15, 15 });
	mRoller.setFillColor(sf::Color::Yellow);
	mRoller.setPosition(initPosition.x + 15, initPosition.y + 50);

	MovementSpeed = 300.f;
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(mBody);
	window.draw(mRoller);

	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i]->draw(window);
		if (Bullets[i]->getPosition().x > 1366.f ||
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		fireBullet();
	}

	
}

void Player::handelMovement(sf::Time& dt)
{
	static sf::Clock clock;
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

void Player::fireBullet()
{
	static sf::Clock clock;
	if (clock.getElapsedTime()	> sf::seconds(.2f) &&
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

		clock.restart();
	}
}
