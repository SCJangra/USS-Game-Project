#include "stdafx.h"
#include "Player.h"

const float Player::MovementSpeed = 200.f;

Player::Player(sf::Vector2f initPosition)
	: mBody({ 30, 50 })
	, mRoller(15)
	, mIsMovingDown(false)
	, mIsOnPlatform(false)
	, mMovement(0.f, 0.f)
{
	mBody.setPosition({ initPosition.x, initPosition.y });
	mBody.setOrigin({ 15, 25 });
	mBody.setFillColor(sf::Color::Green);

	mRoller.setOrigin({ 15, 15 });
	mRoller.setFillColor(sf::Color::Yellow);
	mRoller.setPosition(initPosition.x, initPosition.y + 25);
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(mBody);
	window.draw(mRoller);
}

void Player::move(sf::Vector2f distance)
{
	mBody.move(distance);
	mRoller.move(distance);
	mIsOnPlatform = false;
}

void Player::update(sf::Time dt)
{
	handelInput(dt);
}

bool Player::isOnPlatform()
{
	return mIsOnPlatform;
}

void Player::setOnPlatform(bool onPlatform)
{
	mIsOnPlatform = onPlatform;
}

const sf::Vector2f Player::getLoverBound()
{
	return sf::Vector2f(mRoller.getPosition().x, mRoller.getPosition().y + 15);
}

bool Player::isFalling()
{
	return mIsMovingDown;
}




Player::~Player()
{
}

void Player::handelInput(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= MovementSpeed;
		mIsMovingDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= MovementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += MovementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += MovementSpeed;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !mIsOnPlatform) {
		movement.y += MovementSpeed;
		mIsMovingDown = true;
	}
	
	move(movement * dt.asSeconds());
}
