// DglImage.cpp

#include "DglImage.h"

#include "bitmap_class.h"

bool CDglImage::LoadImageFile(const char *szFileName)
{
	//here we figure out what type of file we are dealing with
	//maybe even load the file here?
	
	//assuming bmp file format
	
	if (!cbitmap.loadBMP(szFileName))
	{
		return false;
	}
	iWidth = cbitmap.getWidth();
	iHeight = cbitmap.getHeight();
	iBits = cbitmap.getChannels();
	pcData = cbitmap.getLinePtr(0);

	return true;
}
