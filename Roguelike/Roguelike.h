#pragma once

class Roguelike
{
	
	Roguelike() = default;
	~Roguelike() = default;

public:
	Roguelike(const Roguelike&) = delete;
	Roguelike& operator=(const Roguelike&) = delete;
	Roguelike(Roguelike&) = delete;
	Roguelike& operator=(Roguelike&&) = delete;

	static Roguelike& GetInstance();
private:
	bool bIsRunning = false;

public:
	void Ini();
	void Stop();

private:
	void Run();
};