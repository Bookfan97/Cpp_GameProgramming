#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"

using namespace sf;

class Engine
{
private:
	TextureHolder th;
	Thomas m_Thomas;
	Bob m_Bob;
	LevelManager m_LM;
	SoundManager m_SM;
	HUD m_HUD;
	int m_FramesSinceLastHUDUpdate = 0, m_TargetFramesSinceLastHUDUpdate = 500;
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	const int GRAVITY = 300;
	RenderWindow m_Window;
	View m_MainView, m_LeftView, m_RightView, m_BGMainView, m_BGLeftView, m_BGRightView, m_HudView;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	bool m_Playing = false, m_Character1 = true, m_SplitScreen = false, m_NewLevelRequired = true;
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;
	VertexArray m_VALevel;
	int** m_ArrayLevel = NULL;
	Texture m_TextureTiles;
	void input();
	void update(float dtAsSeconds);
	void draw();
	void loadLevel();
	bool detectCollisions(PlayableCharacter& character);
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);
	vector <Vector2f> m_FireEmitters;
public:
	Engine();
	void run();
};