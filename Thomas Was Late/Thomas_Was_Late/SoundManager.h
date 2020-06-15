#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
	SoundBuffer m_FireBuffer, m_FallInFireBuffer, m_FallInWaterBuffer, m_JumpBuffer, m_ReachGoalBuffer;
	Sound m_Fire1Sound, m_Fire2Sound, m_Fire3Sound, m_FallInFireSound, m_FallInWaterSound, m_JumpSound, m_ReachGoalSound;
	int m_NextSound = 1;
public:
	SoundManager();
	void playFire(Vector2f emitterLocation, Vector2f listenerLocation);
	void playFallInFire();
	void playFallInWater();
	void playJump();
	void playReachGoal();
};