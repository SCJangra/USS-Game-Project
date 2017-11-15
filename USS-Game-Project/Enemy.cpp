#include "stdafx.h"
#include "Enemy.h"

const float Enemy::MovementSpeed = 200.f;

Enemy::Enemy()
	: leftContact(false)
	, rightContact(false)
	, bottomContact(false)
	, mBody(sf::RectangleShape())
{
	std::random_device rd;								// obtain a random number from hardware
	std::mt19937 eng(rd());								// seed the generator
	std::uniform_real_distribution<> distr(31.f, 1335.f);	// define the range
	std::uniform_int_distribution<> rand(0, 1);

	mBody.setSize({ 30, 65 });
	mBody.setPosition((float)distr(eng), -67.f);
	mBody.setFillColor(sf::Color::White);

	initMovement();
}

void Enemy::update(sf::Time dt)
{
	move(dt);
}

void Enemy::move(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);

	// Move down if not standing on any platform
	if (!bottomContact)			movement.y += MovementSpeed;

	// Change direction if left collision detected
	if (!leftContact && bottomContact && !mIsMovingRight) {
		movement.x -= MovementSpeed;
	}
	else if (leftContact && bottomContact && !mIsMovingRight) {
		movement.x += MovementSpeed;
		mIsMovingRight = true;
	}

	// Change direction if right collision detected
	if (!rightContact && bottomContact && mIsMovingRight) {
		movement.x += MovementSpeed;
	}
	else if (rightContact && bottomContact && mIsMovingRight) {
		movement.x -= MovementSpeed;
		mIsMovingRight = false;
	}
	mBody.move(movement * dt.asSeconds());

	leftContact = false;
	rightContact = false;
	bottomContact = false;
}

const sf::RectangleShape& Enemy::getBody()
{
	return mBody;
}

void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(mBody);
}

bool check(const std::vector<RectPointer>& platforms, sf::Vector2f& point) {
	sf::Vector2f platformPosition;
	sf::Vector2f platformSize;
	for (int i = 0; i < platforms.size(); i++) {
		platformPosition = platforms[i].get()->getPosition();
		platformSize = platforms[i].get()->getSize();

		if (
			point.x + 2 >= platformPosition.x &&
			point.y + 2 >= platformPosition.y &&
			point.x - 2 <= platformPosition.x + platformSize.x &&
			point.y - 2 <= platformPosition.y + platformSize.y
			)
		{
			return true;
		}
	}
	return false;
}

void Enemy::calculateCollisions(const std::vector<RectPointer>& platforms)
{
	sf::Vector2f collisionPoint;
	if (!bottomContact) {
		bool l, r;
		collisionPoint = mBody.getPosition() + mBody.getSize();
		l = check(platforms, collisionPoint);
		collisionPoint.x = mBody.getPosition().x;
		collisionPoint.y = mBody.getPosition().y + mBody.getSize().y;
		r = check(platforms, collisionPoint);
		bottomContact = l || r;
	}
	if (bottomContact && mIsMovingRight) {
		collisionPoint.x = mBody.getPosition().x + mBody.getSize().x;
		collisionPoint.y = mBody.getPosition().y;
		rightContact = check(platforms, collisionPoint);
	}
	if (bottomContact && !mIsMovingRight) {
		collisionPoint = mBody.getPosition();
		leftContact = check(platforms, collisionPoint);
	}
}

void Enemy::initMovement()
{
	std::random_device rd;								// obtain a random number from hardware
	std::mt19937 eng(rd());								// seed the generator
	std::uniform_int_distribution<> rand(0, 1);

	int r = rand(eng);
	if (r == 0) {
		mIsMovingRight = false;
	}
	else if (r == 1) {
		mIsMovingRight = true;
	}
}
