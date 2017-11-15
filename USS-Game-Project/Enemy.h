#pragma once
#include "ResourceIdentifiers.h"
class Enemy
{
public:
	Enemy();
	void							update(sf::Time dt);
	void							move(sf::Time dt);
	const sf::RectangleShape&		getBody();
	void							draw(sf::RenderWindow& window);
	void							calculateCollisions(const std::vector<RectPointer>& platforms);

public:

	bool							leftContact;
	bool							rightContact;
	bool							bottomContact;

private:
	void							initMovement();

private:
	
	sf::RectangleShape				mBody;

	static const float				MovementSpeed;

	bool							mIsMovingRight;
};

