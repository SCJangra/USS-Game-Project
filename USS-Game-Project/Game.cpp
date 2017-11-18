#include "stdafx.h"

const	float		Game::PlayerSpeed = 100.f;
const	sf::Time	Game::TimePerFrame = sf::seconds(1.f / 60.f);
		int			Game::Score = 0;

Game::Game()
	: mWindow(sf::VideoMode(1920, 1080), "USS", sf::Style::Fullscreen)
	, mWorld(mWindow)
	, mFont()
	, mStatisticsText()
	, mScoreText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mFont.loadFromFile("Assets/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(35.f, 5.f);
	mStatisticsText.setCharacterSize(20);

	mScoreText.setFont(mFont);
	mScoreText.setPosition({ mWindow.getSize().x - 200.f, 5.f });
	mScoreText.setCharacterSize(20);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();
	mWindow.draw(mStatisticsText);
	mWindow.draw(mScoreText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;

		mScoreText.setString("Score: " + std::to_string(Score));
	}
}
