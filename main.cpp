// main.cpp

#include <windows.h>

#include "DglCheckers3d.h"

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	CDglCheckers3d game;
	return game.GameLoop();
}

