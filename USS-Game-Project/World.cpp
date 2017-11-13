#include "stdafx.h"
#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f);
}

void World::update(sf::Time dt)
{
}

void World::draw()
{
	mWindow.setView(mWorldView);
}

void World::loadTextures()
{
	mTextures.load(Textures::Desert, "Assets/Textures/Background.jpg");
}

void World::buildScene()
{

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
}