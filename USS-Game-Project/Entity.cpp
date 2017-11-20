#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
	: mIsMovingRight(false)
	, mLeftContact(false)
	, mRightContact(false)
	, mBottomContact(false)
	, mTopContact(false)
	, mBody(sf::RectangleShape())
	, mTexture()
{
}

void Entity::calculateCollisions(const std::vector<RectPointer>& platforms)
{
	sf::Vector2f collisionPoint;
	EntityBounds bounds = getEntityBounds();
	bool l, r;

	// Check Bottom Contact
	collisionPoint = bounds.position + bounds.size;
	l = checkCollision(platforms, collisionPoint);
	collisionPoint.x = bounds.position.x;
	collisionPoint.y = bounds.position.y + bounds.size.y;
	r = checkCollision(platforms, collisionPoint);
	mBottomContact = l || r;

	// Check Top Contact
	collisionPoint = bounds.position;
	l = checkCollision(platforms, collisionPoint);
	collisionPoint.x = bounds.position.x + bounds.size.x;
	collisionPoint.y = bounds.position.y;
	r = checkCollision(platforms, collisionPoint);
	mTopContact = l || r;

	// Check Right Contact
	collisionPoint.x = bounds.position.x + bounds.size.x;
	collisionPoint.y = bounds.position.y;
	mRightContact = checkCollision(platforms, collisionPoint);

	// Check Left Contact
	collisionPoint = bounds.position;
	mLeftContact = checkCollision(platforms, collisionPoint);
}

bool Entity::checkCollision(const std::vector<RectPointer>& platforms, sf::Vector2f& point)
{
	sf::Vector2f platformPosition;
	sf::Vector2f platformSize;
	for (int i = 0; i < platforms.size(); i++) {
		platformPosition = platforms[i].get()->getPosition();
		platformSize = platforms[i].get()->getSize();

		if (
			point.x + 2 >= platformPosition.x &&
			point.y     >= platformPosition.y &&
			point.x - 2 <= platformPosition.x + platformSize.x &&
			point.y     <= platformPosition.y + platformSize.y
			)
		{
			return true;
		}
	}
	return false;
}
