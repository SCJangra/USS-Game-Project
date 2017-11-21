#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(bool isFiredTowardsRight)
	: mBullet()
{
	mBullet.setSize({ 75.f, 7.f });
	mIsFiredTowardsRight = isFiredTowardsRight;
}

void Bullet::update(sf::Time & dt)
{
	if (mIsFiredTowardsRight) {
		mBullet.move({ 900 * dt.asSeconds(), 0.f });
	}
	else {
		mBullet.move({ -900 * dt.asSeconds(), 0.f });
	}
}

void Bullet::draw(sf::RenderWindow & window)
{
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

sf::Vector2f Bullet::getSize()
{
	return mBullet.getSize();
}

void Bullet::setTexture(sf::Texture & texture)
{
	mBullet.setTexture(&texture);
}