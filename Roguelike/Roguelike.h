#pragma once

class Roguelike
{
public:
	~Roguelike();

private:
	bool bIsRunning;

public:
	void Ini();

private:
	void Run();
};