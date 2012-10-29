// DglImage.h

#include "bitmap_class.h"

class CDglImage
{
public:
	bool LoadImageFile(const char* szFileName);

	int iWidth;
	int iHeight;
	int iBits;
	unsigned char* pcData;
private:
	CBitmap cbitmap;
};
