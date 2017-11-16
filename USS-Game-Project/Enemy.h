#pragma once
#include "ResourceIdentifiers.h"
class Enemy : public Entity
{
public:
	Enemy();
	void							update(sf::Time dt);
	void							draw(sf::RenderWindow& window);
	const EntityBounds				getEntityBounds();
	void							handelMovement(sf::Time& dt);
	void							checkBulletHit(std::vector<std::unique_ptr<Bullet>>& platforms);

public:
	int								HitCount;
private:
	void							initMoveDirection();
};