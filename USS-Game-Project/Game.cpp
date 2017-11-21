#include "stdafx.h"

const	float		Game::PlayerSpeed = 100.f;
const	sf::Time	Game::TimePerFrame = sf::seconds(1.f / 60.f);
		int			Game::Score = 0;
		int			Game::Health = 10;

Game::Game()
	: mWindow(sf::VideoMode(1920, 1080), "USS", sf::Style::Fullscreen)
	, mWorld(mWindow)
	, mFont()
	, mStatisticsText()
	, mScoreText()
	, mHealthText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mBGMusic()
	, mGameOverFont()
	, mGameOverText()
{
	mGameOverFont.loadFromFile("Assets/LittleLordFontleroyNF.ttf");
	mGameOverText.setFont(mGameOverFont);
	mGameOverText.setCharacterSize(200);
	mGameOverText.setPosition({ 600.f, 300.f });
	mGameOverText.setString("Game Over");

	// Start Playing the music
	mBGMusic.openFromFile("Assets/Music/BGMusic/MegaMan3All.ogg");
	mBGMusic.play();
	mBGMusic.setVolume(100.f);
	mBGMusic.setPlayingOffset(sf::seconds(60 * 4 + 50));

	// Load font and set text properties
	mFont.loadFromFile("Assets/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(25.f, 25.f);
	mStatisticsText.setCharacterSize(20);

	mScoreText.setFont(mFont);
	mScoreText.setPosition({ mWindow.getSize().x - 200.f, 25.f });
	mScoreText.setCharacterSize(20);

	mHealthText.setFont(mFont);
	mHealthText.setPosition({ mWindow.getSize().x / 2.f, 25.f });
	mHealthText.setCharacterSize(20);
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
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	if (Health > 0) mWorld.update(elapsedTime);
	else {
		mBGMusic.stop();
	}
}

void Game::render()
{
	mWindow.clear();
	if (Health > 0) {
		mWorld.draw();
		mWindow.draw(mStatisticsText);
		mWindow.draw(mScoreText);
		mWindow.draw(mHealthText);
	}
	else {
		mWindow.draw(mGameOverText);
	}
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
		mHealthText.setString("Health: " + std::to_string(Health));
	}
}
