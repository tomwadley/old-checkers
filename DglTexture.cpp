// DglTexture.cpp

#include <windows.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

//this is for devc++
#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif 

#include "DglTexture.h"

#include "DglImage.h"


bool CDglTexture::LoadTexture(const char* szFileName)
{
	CDglImage dglimage;
	if (!dglimage.LoadImageFile(szFileName))
	{
		return false;
	}

	glGenTextures(1, &gTextureID);
	glBindTexture(GL_TEXTURE_2D, gTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, dglimage.iBits, dglimage.iWidth, dglimage.iHeight,
				 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLvoid*)dglimage.pcData);
	if (gluBuild2DMipmaps(GL_TEXTURE_2D, dglimage.iBits, dglimage.iWidth, 
					  dglimage.iHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
					  (GLvoid*)dglimage.pcData) != 0)
	{
		FreeTexture();
		return false;
	}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	

	return true;
}

void CDglTexture::FreeTexture()
{
	if(gTextureID) // If we loaded a texture
	{
		glDeleteTextures(1,&gTextureID); // Free up the texture
	}

	gTextureID = 0;
}
