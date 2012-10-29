// DglOpenGl.h

#ifndef DGLOPENGL_H
#define DGLOPENGL_H

#include <windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

const char szWindowClassName[] = "DglOpenGl";

class CDglOpenGl
{
public:
	CDglOpenGl(){ZeroMemory(this, sizeof(*this));}
	~CDglOpenGl(){DestroyOpenGlWindow();}

	bool CreateOpenGlWindow(const char* pcTitle, int iWidth, int iHeight, int iBits, bool bFullscreen, WNDPROC WndProc);
	void SizeScene(GLsizei iWidth, GLsizei iHeight);
	void DestroyOpenGlWindow();
	
	void PopOrthoMode();
	void PushOrthoMode();

	//GET DATA
	HWND GetHWND(){return hWnd;}
	HDC GetHDC(){return hDC;}
	int GetWindowWidth(){return iWindowWidth;}
	int GetWindowHeight(){return iWindowHeight;}
private:
	HWND hWnd; //window handle
	HDC hDC; //device context
	HGLRC hRC; //rendering context
	
	int iWindowWidth, iWindowHeight;

	bool bWindowIsFullScreen;
};

#endif

