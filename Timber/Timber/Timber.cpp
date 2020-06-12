#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace sf;
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber", Style::Fullscreen);
	Texture textureBackground;
	textureBackground.loadFromFile("../graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	Texture textureTree;
	textureTree.loadFromFile("../graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);
	Texture textureTree2;
	textureTree2.loadFromFile("../graphics/tree2.png");
	const int NUM_TREES = 6;
	Sprite trees[NUM_TREES];
	for (int i = 0; i < NUM_TREES; i++)
	{
		trees[i].setTexture(textureTree2);
		trees[i].setPosition((rand() % 1920), (rand() % 540) - 540);
	}
	Texture textureBee;
	textureBee.loadFromFile("../graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;
	Texture textureCloud;
	textureCloud.loadFromFile("../graphics/cloud.png");
	const int NUM_CLOUDS = 6;
	Sprite clouds[NUM_CLOUDS];
	int cloudSpeeds[NUM_CLOUDS];
	bool cloudsActive[NUM_CLOUDS];
	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		clouds[i].setTexture(textureCloud);
		clouds[i].setPosition(-300, i * 150);
		cloudsActive[i] = false;
		cloudSpeeds[i] = 0;
	}
	Clock clock;
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	bool paused = true;
	int score = 0;
	Text messageText;
	Text scoreText;
	Text fpsText;
	Font font;
	font.loadFromFile("../fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	fpsText.setFont(font);
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(20);
	fpsText.setPosition(1750, 25);
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);
	RectangleShape rect1;
	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600, 105));
	rect1.setPosition(0, 30);
	RectangleShape rect2;
	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(150, 30));
	rect2.setPosition(1750, 20);
	Texture textureBranch;
	textureBranch.loadFromFile("../graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}
	Texture texturePlayer;
	texturePlayer.loadFromFile("../graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;
	Texture textureDead;
	textureDead.loadFromFile("../graphics/rip.png");
	Sprite spriteDead;
	spriteDead.setTexture(textureDead);
	spriteDead.setPosition(600, 860);
	Texture textureAxe;
	textureAxe.loadFromFile("../graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	const float AXE_POSITION_LEFT = 830, AXE_POSITION_RIGHT = 1075;
	Texture textureLog;
	textureLog.loadFromFile("../graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	bool logActive = false, acceptInput = false;
	float logSpeedX = 1000, logSpeedY = -1500;
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("../sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("../sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("../sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);
	int lastDrawn = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			score = 0;
			timeRemaining = 6;
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}
			spriteDead.setPosition(675, 2000);
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}
		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			{
				playerSide = side::RIGHT;
				score++;
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spriteAxe.setScale(sf::Vector2f(1, 1));
				spritePlayer.setPosition(1200, 720);
				spritePlayer.setScale(sf::Vector2f(1, 1));
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			{
				playerSide = side::LEFT;
				score++;
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spriteAxe.setScale(sf::Vector2f(-1, 1));
				spritePlayer.setPosition(700, 720);
				spritePlayer.setScale(sf::Vector2f(-1, 1));
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}
		}
		if (!paused)
		{
			Time dt = clock.restart();
			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f) {
				paused = true;
				messageText.setString("Out of time!!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				outOfTime.play();
			}
			if (!beeActive)
			{
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}
			for (int i = 0; i < NUM_CLOUDS; i++)
			{
				if (!cloudsActive[i])
				{
					srand((int)time(0) * i);
					cloudSpeeds[i] = (rand() % 200);
					srand((int)time(0) * i);
					float height = (rand() % 150);
					clouds[i].setPosition(-200, height);
					cloudsActive[i] = true;
				}
				else
				{
					clouds[i].setPosition(clouds[i].getPosition().x + (cloudSpeeds[i] * dt.asSeconds()), clouds[i].getPosition().y);
					if (clouds[i].getPosition().x > 1920)
					{
						cloudsActive[i] = false;
					}
				}
			}
			lastDrawn++;
			if (lastDrawn == 100)
			{
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
				std::stringstream ss2;
				ss2 << "FPS = " << 1 / dt.asSeconds();
				fpsText.setString(ss2.str());
				lastDrawn = 0;
			}
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					branches[i].setPosition(610, height);
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(0);
				}
				else
				{
					branches[i].setPosition(3000, height);
				}
			}
			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}
			if (branchPositions[5] == playerSide)
			{
				paused = true;
				acceptInput = false;
				spriteDead.setPosition(525, 760);
				spritePlayer.setPosition(3000, 660);
				messageText.setString("LOOKS LIKE YOU GOT STUMPED");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				death.play();
			}
		}
		window.clear();
		window.draw(spriteBackground);
		for (int i = 0; i < NUM_CLOUDS; i++)
		{
			window.draw(clouds[i]);
		}
		for (int i = 0; i < NUM_TREES; i++)
		{
			window.draw(trees[i]);
		}
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		window.draw(spriteTree);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteDead);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(fpsText);
		window.draw(timeBar);
		if (paused)
		{
			window.draw(messageText);
		}
		window.display();
	}
	return 0;
}

void updateBranches(int seed)
{
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}