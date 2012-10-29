// DglGameMenu.cpp

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include "DglGameMenu.h"

CDglGameMenu::CDglGameMenu()
{
    iNumberOfItems = 0;
    amenuitemItems = NULL;
    bItemSelected = false;
    iSelectedItem = 0;
    iMenuItemWidth = 0;
    iMenuItemHeight = 0;
}    

bool CDglGameMenu::CreateItemList(int iNumItems)
{
    DestroyItemList();
    amenuitemItems = new MenuItem[iNumItems];
    if (!amenuitemItems)
    {
        return false;
    }
    iNumberOfItems = iNumItems;
    for (int i = 0; i < iNumItems; i++)
    {
        amenuitemItems[i].bSelectable = false;
        amenuitemItems[i].bVisible = false;
    }
    return true;
}    

void CDglGameMenu::DestroyItemList()
{
    if (amenuitemItems)
    {
        delete[] amenuitemItems;
    }
    iNumberOfItems = 0;
    amenuitemItems = NULL;
    bItemSelected = false;
    iSelectedItem = 0;
}    

void CDglGameMenu::DrawOgl()
{
    int iNumberOfVisibleItems = 0;
    for (int i = 0; i < iNumberOfItems; i++)
    {
        if (amenuitemItems[i].bVisible)
        {
            iNumberOfVisibleItems ++;
        }
    }   
    
    int iDistanceFromTop = (iScreenHeight - (iNumberOfVisibleItems * iMenuItemHeight)) / 2;
    int iDistanceFromLeft = (iScreenWidth - iMenuItemWidth) / 2;
    
    for (int i = 0; i < iNumberOfItems; i++)
    {
        if (amenuitemItems[i].bVisible)
        {
            glColor3ub(255,255,255);
        	glDisable(GL_DEPTH_TEST);
        	glBlendFunc(GL_DST_COLOR,GL_ZERO);
        	glEnable(GL_BLEND);							
        	glBindTexture(GL_TEXTURE_2D,  amenuitemItems[i].dgltextureMaskPic.GetTextureID());
        	glBegin(GL_QUADS);
        		// Display the top left point of the 2D image
        		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop);
        		// Display the bottom left point of the 2D image
        		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop+iMenuItemHeight);
        		// Display the bottom right point of the 2D image
        		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop+iMenuItemHeight);
        		// Display the top right point of the 2D image
        		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop);
        	glEnd();
        	glBlendFunc(GL_ONE,GL_ONE);
        	if (!amenuitemItems[i].bSelectable)
        	{
        	    glColor3ub(80,80,80);
        	}    
        	glBindTexture(GL_TEXTURE_2D,  amenuitemItems[i].dgltexturePic.GetTextureID());
        	glBegin(GL_QUADS);
        		// Display the top left point of the 2D image
        		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop);
        		// Display the bottom left point of the 2D image
        		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop+iMenuItemHeight);
        		// Display the bottom right point of the 2D image
        		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop+iMenuItemHeight);
        		// Display the top right point of the 2D image
        		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop);
        	glEnd();
        	glDisable(GL_BLEND);
        	glEnable(GL_DEPTH_TEST);
        	
        	if ((i == iSelectedItem) & bItemSelected)
        	{
        	    glColor3ub(255,255,255);
            	glDisable(GL_DEPTH_TEST);
            	glBlendFunc(GL_DST_COLOR,GL_ZERO);
            	glEnable(GL_BLEND);							
            	glBindTexture(GL_TEXTURE_2D,  dgltextureMaskSelect.GetTextureID());
            	glBegin(GL_QUADS);
            		// Display the top left point of the 2D image
            		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop);
            		// Display the bottom left point of the 2D image
            		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop+iMenuItemHeight);
            		// Display the bottom right point of the 2D image
            		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop+iMenuItemHeight);
            		// Display the top right point of the 2D image
            		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop);
            	glEnd();
            	glBlendFunc(GL_ONE,GL_ONE);  
            	glBindTexture(GL_TEXTURE_2D,  dgltextureSelect.GetTextureID());
            	glBegin(GL_QUADS);
            		// Display the top left point of the 2D image
            		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop);
            		// Display the bottom left point of the 2D image
            		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, iDistanceFromTop+iMenuItemHeight);
            		// Display the bottom right point of the 2D image
            		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop+iMenuItemHeight);
            		// Display the top right point of the 2D image
            		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+iMenuItemWidth, iDistanceFromTop);
            	glEnd();
            	glDisable(GL_BLEND);
            	glEnable(GL_DEPTH_TEST);       	
        	}   	 
            
        	iDistanceFromTop += iMenuItemHeight;
        }
    }        
}

void CDglGameMenu::ModifySelectionUpOrDown(bool bUp)
{
    int iChangeToSelection;
    if (bUp)
    {
        iChangeToSelection = -1;
    }
    else
    {
        iChangeToSelection = 1;
    }    
    int iStartingSelection = iSelectedItem;
    while (!(amenuitemItems[iSelectedItem].bVisible & amenuitemItems[iSelectedItem].bSelectable) | (iSelectedItem == iStartingSelection))
    {
        iSelectedItem += iChangeToSelection;
        if (iSelectedItem < 0)
        {
            iSelectedItem = iNumberOfItems -1;
        }
        if (iSelectedItem >= iNumberOfItems)
        {
            iSelectedItem = 0;
        }
        if (!bItemSelected & (iChangeToSelection == 1))
        {
            iSelectedItem = 0;
            iStartingSelection = iNumberOfItems -1;
        }
        if (!bItemSelected & (iChangeToSelection == -1))
        {
            iSelectedItem = iNumberOfItems -1;
            iStartingSelection = 0;
        }    
        bItemSelected = true;     
        if (iSelectedItem == iStartingSelection)
        {
            iSelectedItem = 0;
            bItemSelected = false;
            return;
        }
    }
}

void CDglGameMenu::ModifySelectionFromMouse(long lMouseX, long lMouseY)
{
    int iNumberOfVisibleItems = 0;
    for (int i = 0; i < iNumberOfItems; i++)
    {
        if (amenuitemItems[i].bVisible)
        {
            iNumberOfVisibleItems ++;
        }
    }   
    
    int iDistanceFromTop = (iScreenHeight - (iNumberOfVisibleItems * iMenuItemHeight)) / 2;
    int iDistanceFromLeft = (iScreenWidth - iMenuItemWidth) / 2;
    
    //no selection
    bItemSelected = false;
    iSelectedItem = 0;
    
    //make selection
    for (int i = 0; i < iNumberOfItems; i++)
    {
        if (amenuitemItems[i].bVisible)
        {
            if ((lMouseX >= iDistanceFromLeft) & (lMouseX <= (iDistanceFromLeft+iMenuItemWidth)) & (lMouseY >= iDistanceFromTop) & (lMouseY <= (iDistanceFromTop+iMenuItemHeight)))
            {
                if (amenuitemItems[i].bSelectable)
                {
                    //select this
                    bItemSelected = true;
                    iSelectedItem = i;
                }
            }
            iDistanceFromTop += iMenuItemHeight;
        } 
    }                
}

void CDglGameMenu::SetItemDimensions(int iWidth, int iHeight)
{
    iMenuItemWidth = iWidth;
    iMenuItemHeight = iHeight;
}

void CDglGameMenu::SetScreenDimensions(int iWidth, int iHeight)
{
    iScreenWidth = iWidth;
    iScreenHeight = iHeight;
}    

void CDglGameMenu::Unselect()
{
    bItemSelected = false;
    iSelectedItem = 0;
}

void CDglGameMenu::Select(int iItem) 
{
    if (iItem >= iNumberOfItems)
    {
        iSelectedItem = 0; //error
    }    
    iSelectedItem = iItem;  
}
    
