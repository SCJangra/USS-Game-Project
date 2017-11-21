#pragma once
class Game : private sf::NonCopyable
{
public:		// Public Functions
	Game();
	void					run();

public:		// Public Static Data
	static int				Score;
	static int				Health;


private:	// Private Functions
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();
	void					gameOver();
	void					updateStatistics(sf::Time elapsedTime);


private:	// Private Data
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Font				mFont;
	sf::Font				mGameOverFont;
	sf::Text				mGameOverText;
	sf::Text				mScoreText;
	sf::Text				mHealthText;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	sf::Music				mBGMusic;

	std::size_t				mStatisticsNumFrames;

	World					mWorld;
};