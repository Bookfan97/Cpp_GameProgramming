#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"

using namespace sf;

class Engine
{
private:
	TextureHolder th;
	Thomas m_Thomas;
	Bob m_Bob;
	LevelManager m_LM;

	const int TILE_SIZE = 50, VERTS_IN_QUAD = 4, GRAVITY = 300;
	RenderWindow m_Window;
	View m_MainView, m_LeftView, m_RightView, m_BGMainView, m_BGLeftView, m_BGRightView, m_HudView;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	bool m_Playing = false, m_Character1 = true, m_SplitScreen = false, m_NewLevelRequired = true;
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;
	VertexArray M_VALevel;
	int** m_ArrayLevel = NULL;
	Texture m_TextureTiles;
	void input();
	void update(float dtAsSeconds);
	void draw();
	void loadLevel();
public:
	Engine();
	void run();
};