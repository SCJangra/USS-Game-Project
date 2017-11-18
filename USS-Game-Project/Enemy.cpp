#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy() : Entity()
{
	std::random_device rd;								// obtain a random number from hardware
	std::mt19937 eng(rd());								// seed the generator
	std::uniform_real_distribution<> distr(31.f, 1335.f);	// define the range
	std::uniform_int_distribution<> rand(0, 1);

	mBody.setSize({ 30, 65 });
	mBody.setPosition((float)distr(eng), -67.f);
	mBody.setFillColor(sf::Color::White);

	HitCount = 0;

	initMoveDirection();
}

void Enemy::update(sf::Time dt)
{
	handelMovement(dt);
}

void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(mBody);
}

const Entity::EntityBounds Enemy::getEntityBounds()
{
	EntityBounds bounds;
	bounds.position = mBody.getPosition();
	bounds.size = mBody.getSize();
	return bounds;
}

void Enemy::handelMovement(sf::Time& dt)
{
	sf::Vector2f movement(0.f, 0.f);

	// Move down if not standing on any platform
	if (!mBottomContact)			movement.y += MovementSpeed;

	// Change direction if left collision detected
	if (!mLeftContact && mBottomContact && !mIsMovingRight) {
		movement.x -= MovementSpeed;
	}
	else if (mLeftContact && mBottomContact && !mIsMovingRight) {
		movement.x += MovementSpeed;
		mIsMovingRight = true;
	}

	// Change direction if right collision detected
	if (!mRightContact && mBottomContact && mIsMovingRight) {
		movement.x += MovementSpeed;
	}
	else if (mRightContact && mBottomContact && mIsMovingRight) {
		movement.x -= MovementSpeed;
		mIsMovingRight = false;
	}

	if (mBody.getPosition().x <= -64 && !mIsMovingRight) {
		mBody.setPosition({ 1920, mBody.getPosition().y });
	}
	else if (mBody.getPosition().x >= 1920 && mIsMovingRight) {
		mBody.setPosition({ 0, mBody.getPosition().y - 64});
	}
	mBody.move(movement * dt.asSeconds());

	mLeftContact = false;
	mRightContact = false;
	mBottomContact = false;
}

void Enemy::checkBulletHit(std::vector<std::unique_ptr<Bullet>>& bullets)
{
	sf::Vector2f bulletPosition;
	sf::Vector2f bulletSize({ 75, 7 });
	for (int i = 0; i < bullets.size(); i++) {
		bulletPosition = bullets[i]->getPosition();
		if (
			bulletPosition.x >= mBody.getPosition().x &&
			bulletPosition.y >= mBody.getPosition().y &&
			bulletPosition.x <= mBody.getPosition().x + mBody.getSize().x &&
			bulletPosition.y <= mBody.getPosition().y + mBody.getSize().y
			) {
			bullets.erase(bullets.begin() + i);
			HitCount++;
		}
	}
}

void Enemy::initMoveDirection()
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