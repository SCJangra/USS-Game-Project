#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(bool isFiredTowardsRight)
	: mBullet()
{
	mBullet.setSize({ 75.f, 7.f });
	mBullet.setFillColor(sf::Color::White);
	mIsFiredTowardsRight = isFiredTowardsRight;
}

void Bullet::draw(sf::RenderWindow & window)
{
	if (mIsFiredTowardsRight) {
		mBullet.move({ 3.f, 0.f });
	}
	else {
		mBullet.move({ -3.f, 0.f });
	}
	window.draw(mBullet);
}

void Bullet::setPosition(sf::Vector2f position)
{
	mBullet.setPosition(position);
}

sf::Vector2f Bullet::getPosition()
{
	if (mIsFiredTowardsRight) {
		sf::Vector2f p;
		p.x = mBullet.getPosition().x + mBullet.getSize().x;
		p.y = mBullet.getPosition().y;
		return p;
	}
	else {
		return mBullet.getPosition();
	}
}

sf::Vector2f Bullet::getSize()
{
	return mBullet.getSize();
}

void Bullet::setTexture(sf::Texture & texture)
{
	mBullet.setTexture(&texture);
}