#ifndef GAMETIME_H
#define GAMETIME_H

class GameTime
{
public:
	static void Update();
	static float deltaTime();

private:
	static float m_lastFrame;
	static float m_deltaTime;
};
#endif