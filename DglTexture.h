// DglTexture.h

#ifndef	DGLTEXTURE_H
#define	DGLTEXTURE_H

#include <windows.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

class CDglTexture
{
public:
	CDglTexture(){gTextureID = 0;}
	~CDglTexture(){FreeTexture();}

	bool LoadTexture(const char* szFileName);
	void FreeTexture();

	// GET DATA
	GLuint GetTextureID(){return gTextureID;}
private:
	GLuint gTextureID;
};

#endif
