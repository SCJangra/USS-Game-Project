#include "stdafx.h"
#include "Player.h"

const float Player::MovementSpeed = 300.f;

Player::Player(sf::Vector2f initPosition)
	: mBody({ 30, 50 })
	, mRoller(15)
	, mIsMovingDown(false)
	, bottomContact(false)
	, mMovement(0.f, 0.f)
{
	mBody.setPosition({ initPosition.x, initPosition.y });
	//mBody.setOrigin({ 15, 25 });
	mBody.setFillColor(sf::Color::Green);

	mRoller.setOrigin({ 15, 15 });
	mRoller.setFillColor(sf::Color::Yellow);
	mRoller.setPosition(initPosition.x + 15, initPosition.y + 50);
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
	bottomContact = false;
	leftContact = false;
	rightContact = false;
}

void Player::update(sf::Time dt)
{
	handelInput(dt);
}

const sf::Vector2f Player::getLoverBound()
{
	return sf::Vector2f(mRoller.getPosition().x, mRoller.getPosition().y + 15);
}

const sf::Vector2f Player::getLeftBound()
{
	return sf::Vector2f(mBody.getPosition());
}

const sf::Vector2f Player::getRightBound()
{
	return sf::Vector2f(mBody.getPosition().x + 30, mBody.getPosition().y);
}

bool Player::isFalling()
{
	return mIsMovingDown;
}

void Player::handelInput(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= MovementSpeed;
		mIsMovingDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !leftContact)
		movement.x -= MovementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += MovementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !rightContact)
		movement.x += MovementSpeed;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !bottomContact) {
		movement.y += MovementSpeed;
		mIsMovingDown = true;
	}
	
	move(movement * dt.asSeconds());
}
