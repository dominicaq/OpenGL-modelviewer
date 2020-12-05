#ifndef TIME_H
#define TIME_H

class Time
{
public:
	static void Update();
	static float deltaTime();

private:
	static float m_lastFrame;
	static float m_deltaTime;
};
#endif