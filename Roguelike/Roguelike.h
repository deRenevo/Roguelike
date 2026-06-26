#pragma once

class Roguelike
{
public:
	Roguelike() = default;
	~Roguelike() = default;

	static Roguelike& GetInstance();
private:
	bool bIsRunning = false;

public:
	void Ini();
	void Stop();

private:
	void Run();
};