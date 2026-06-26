// main.cpp: определяет точку входа для приложения.
//

#include "Roguelike.h"
#include "raylib.h"
#include <iostream>

using namespace std;

int main()
{
	printf("Hello Roguelike");
	
	Roguelike::GetInstance().Ini();
	return 0;
}
