#pragma once

class Menu;

class Roguelike
{
public:
	Roguelike();
	~Roguelike();

private:
	bool bIsRunning;
	int screenWidth;
	int screenHeight;

	Menu* GameMenu;

public:
	void Ini();
	void Run();
	void Update();
	void Cleanup();
	void InputTick();

	void StopRunning();

};