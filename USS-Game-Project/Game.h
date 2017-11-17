#pragma once
class Game : private sf::NonCopyable
{
public:
	Game();
	void					run();

public:
	static int				Score;


private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();

	void					updateStatistics(sf::Time elapsedTime);


private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Font				mFont;
	sf::Text				mScoreText;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;

	std::size_t				mStatisticsNumFrames;

	World					mWorld;
};