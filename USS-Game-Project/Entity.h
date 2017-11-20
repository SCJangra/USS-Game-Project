#pragma once
#include "ResourceIdentifiers.h"
class Entity
{
protected:
	virtual void						handelMovement(sf::Time& dt) = 0;

	class EntityBounds {
	public:
		sf::Vector2f					position;
		sf::Vector2f					size;
	};
	bool								mIsMovingRight;
	bool								mLeftContact;
	bool								mRightContact;
	bool								mBottomContact;
	bool								mTopContact;
	sf::Texture							mTexture;

public:
	Entity();
	virtual void						update(sf::Time dt)				= 0;
	virtual void						draw(sf::RenderWindow& window)	= 0;
	virtual const EntityBounds			getEntityBounds()				= 0;
	virtual void						calculateCollisions(const std::vector<RectPointer>& platforms);

	sf::RectangleShape					mBody;

private:
	bool								checkCollision(const std::vector<RectPointer>& platforms, sf::Vector2f& point);
};

