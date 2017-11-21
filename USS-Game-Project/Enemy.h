#pragma once
#include "ResourceIdentifiers.h"
class Enemy : public Entity
{
public: // Functions
	Enemy();
	void					update(sf::Time dt);
	void					draw(sf::RenderWindow& window);
	const EntityBounds		getEntityBounds();
	void					handelMovement(sf::Time& dt);
	void					checkBulletHit(std::vector<std::unique_ptr<Bullet>>& platforms);

	static float			MovementSpeed;

public: // Data Members
	int						HitCount;
private: // Data Members
	void					initMoveDirection();
};