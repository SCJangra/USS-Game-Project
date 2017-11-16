#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(bool isFiredTowardsRight)
	: mBullet()
{
	mBullet.setSize({ 10.f, 5.f });
	mBullet.setFillColor(sf::Color::White);
	mIsFiredTowardsRight = isFiredTowardsRight;
}

void Bullet::draw(sf::RenderWindow & window)
{
	if (mIsFiredTowardsRight) {
		mBullet.move({ 1.f, 0.f });
	}
	else {
		mBullet.move({ -1.f, 0.f });
	}
	window.draw(mBullet);
}

void Bullet::setPosition(sf::Vector2f position)
{
	mBullet.setPosition(position);
}

sf::Vector2f Bullet::getPosition()
{
	return mBullet.getPosition();
}
