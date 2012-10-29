// DglCheckers3dDraw.cpp

#include "DglCheckers3d.h"

#define CELL_LENGTH 1
#define HALF_CELL_LENGTH float(CELL_LENGTH) / 2
#define PEICE_LENGTH 0.4
#define HALF_PEICE_LENGTH float(PEICE_LENGTH) / 2

char COLOUR_BUFF_RED = 230;
char COLOUR_BUFF_GREEN = 225;
char COLOUR_BUFF_BLUE = 167;
    
char COLOUR_GREEN_RED = 0;
char COLOUR_GREEN_GREEN = 85;
char COLOUR_GREEN_BLUE = 0;

char COLOUR_RED_RED = 175;
char COLOUR_RED_GREEN = 0;
char COLOUR_RED_BLUE = 0;
    
char COLOUR_KRED_RED = 251;
char COLOUR_KRED_GREEN = 146;
char COLOUR_KRED_BLUE = 4;
    
char COLOUR_BLACK_RED = 0;
char COLOUR_BLACK_GREEN = 0;
char COLOUR_BLACK_BLUE = 0;
    
char COLOUR_KBLACK_RED = 0;
char COLOUR_KBLACK_GREEN = 64;
char COLOUR_KBLACK_BLUE = 160;

void CDglCheckers3d::DrawBoard()
{    
    bool bDrawingGreen = false;
    int x, y;
    for (y = 1; y <= 8; y++)
    {
        bDrawingGreen = !bDrawingGreen;
        for (x = 1; x <= 8; x++)
        {
            float fX = (-(4 * CELL_LENGTH) + HALF_CELL_LENGTH);
            fX += (x-1) * CELL_LENGTH;
            float fY = (-(4 * CELL_LENGTH) + HALF_CELL_LENGTH);
            fY += (y-1) * CELL_LENGTH;
            if (bDrawingGreen)
            {
                glColor3ub(COLOUR_GREEN_RED, COLOUR_GREEN_GREEN, COLOUR_GREEN_BLUE);
                glBindTexture(GL_TEXTURE_2D, dgltextureGreenSquare.GetTextureID());
            }
            else
            {
                glColor3ub(COLOUR_BUFF_RED, COLOUR_BUFF_GREEN, COLOUR_BUFF_BLUE);
                glBindTexture(GL_TEXTURE_2D, dgltextureBuffSquare.GetTextureID());
            }         
            int iId = 100 + (10 * (y-1)) + (x-1);
        	glPushName(iId);
            glBegin(GL_QUADS);
                glNormal3f(0,-1,0);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(fX - HALF_CELL_LENGTH, 0,  fY - HALF_CELL_LENGTH);	// Bottom Left
                glTexCoord2f(1.0f, 0.0f); glVertex3f(fX + HALF_CELL_LENGTH, 0,  fY - HALF_CELL_LENGTH);	// Bottom Right
                glTexCoord2f(1.0f, 1.0f); glVertex3f(fX + HALF_CELL_LENGTH, 0,  fY + HALF_CELL_LENGTH);	// Top Right
                glTexCoord2f(0.0f, 1.0f); glVertex3f(fX - HALF_CELL_LENGTH, 0,  fY + HALF_CELL_LENGTH);	// Top Left
            glEnd();
            glPopName();
            bDrawingGreen = !bDrawingGreen;
        }
    }
    //glDisable(GL_TEXTURE_2D);
}  

void CDglCheckers3d::DrawMovingPeice() //bad code, works
{
    glPushMatrix();
    glTranslatef(-3.5, 0, -3.5);
    if (bTargetSelected)
    {
        if (!moveinfoCurrent.bMoved)
        {
            glTranslatef(aiSelect[cTurn][0],0,aiSelect[cTurn][1]);
            float fX, fY;
            float fUp;
            float fYRotation = 0;
            if (moveinfoCurrent.bCapture)
            {
                float fAlteredProgress = moveinfoCurrent.fProgress - 1;
                if (aiSelect[TARGET][0] > aiSelect[cTurn][0])
                {
                    if (aiSelect[TARGET][1] > aiSelect[cTurn][1])
                    {
                        fYRotation = 315;
                    }
                    else
                    {
                        fYRotation = 45;
                    }
                }
                else
                {
                    if (aiSelect[TARGET][1] > aiSelect[cTurn][1])
                    {
                        fYRotation = 225;
                    }
                    else
                    {
                        fYRotation = 135;
                    }
                }              
                fUp = -(fAlteredProgress*fAlteredProgress) + 1;
                fX = (moveinfoCurrent.fProgress / 2) * (DIAGONAL_CELL_LENGTH*2);
                fY = 0;
                
            }    
            else
            {
                fUp = 0;
                fX = ((aiSelect[TARGET][0] - aiSelect[cTurn][0]) * moveinfoCurrent.fProgress) / DIAGONAL_CELL_LENGTH;
                fY = ((aiSelect[TARGET][1] - aiSelect[cTurn][1]) * moveinfoCurrent.fProgress) / DIAGONAL_CELL_LENGTH;
            }    
                
            // (target - select)*fProgress / constantDiagDistance
            glRotatef(fYRotation,0,1,0);
            glTranslatef(fX,-fUp,fY);
            glRotatef(-fYRotation,0,1,0);
            
            Cell cell = checkersBoard.GetCell(aiSelect[cTurn][0],aiSelect[cTurn][1]);
            if (cell.cOwner == WHITE)
            {
                if (cell.bKing)
                {
                    glColor3ub(COLOUR_KRED_RED, COLOUR_KRED_GREEN, COLOUR_KRED_BLUE);
                    glBindTexture(GL_TEXTURE_2D, dgltextureRedKing.GetTextureID());
                }
                else
                {    
                    glColor3ub(COLOUR_RED_RED, COLOUR_RED_GREEN, COLOUR_RED_BLUE);
                    glBindTexture(GL_TEXTURE_2D, dgltextureRedPeice.GetTextureID());
                }    
            }
            else
            {
               if (cell.bKing)
                {
                    glColor3ub(COLOUR_KBLACK_RED, COLOUR_KBLACK_GREEN, COLOUR_KBLACK_BLUE);
                    glBindTexture(GL_TEXTURE_2D, dgltextureBlackKing.GetTextureID());
                }
                else
                {    
                    glColor3ub(COLOUR_BLACK_RED, COLOUR_BLACK_GREEN, COLOUR_BLACK_BLUE);
                    glBindTexture(GL_TEXTURE_2D, dgltextureBlackPeice.GetTextureID());
                } 
            }
            glBegin(GL_QUADS);
                glNormal3f(0,-1,0);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.1f,  -0.2f);	// Bottom Left Of The Texture and Quad
    		    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f, -0.1f,  -0.2f);	// Bottom Right Of The Texture and Quad
    		    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f,  -0.1f,  0.2f);	// Top Right Of The Texture and Quad
    		    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f,  -0.1f,  0.2f);	// Top Left Of The Texture and Quad
            glEnd();
        }    
    }                
    glPopMatrix();
}    

void CDglCheckers3d::DrawPeices()
{
    int x, y;
    for (y = 1; y <= 8; y++)
    {
        for (x = 1; x <= 8; x++)
        {
            Cell cell = checkersBoard.GetCell((x-1), (y-1));
            if ( !(bTargetSelected & (aiSelect[cTurn][0] == (x-1)) & (aiSelect[cTurn][1] == (y-1))) )
            {
                if (!cell.bEmpty)
                {
                    if (cell.cOwner == WHITE)
                    {
                        if (cell.bKing)
                        {
                            glColor3ub(COLOUR_KRED_RED, COLOUR_KRED_GREEN, COLOUR_KRED_BLUE);
                            glBindTexture(GL_TEXTURE_2D, dgltextureRedKing.GetTextureID());
                        }
                        else
                        {    
                            glColor3ub(COLOUR_RED_RED, COLOUR_RED_GREEN, COLOUR_RED_BLUE);
                            glBindTexture(GL_TEXTURE_2D, dgltextureRedPeice.GetTextureID());
                        }    
                    }
                    else
                    {
                        if (cell.bKing)
                        {
                            glColor3ub(COLOUR_KBLACK_RED, COLOUR_KBLACK_GREEN, COLOUR_KBLACK_BLUE);
                            glBindTexture(GL_TEXTURE_2D, dgltextureBlackKing.GetTextureID());
                        }
                        else
                        {    
                            glColor3ub(COLOUR_BLACK_RED, COLOUR_BLACK_GREEN, COLOUR_BLACK_BLUE);
                            glBindTexture(GL_TEXTURE_2D, dgltextureBlackPeice.GetTextureID());
                        }    
                    }
                    float fX = (-(4 * CELL_LENGTH) + HALF_CELL_LENGTH);
                    fX += (x-1) * CELL_LENGTH;
                    float fY = (-(4 * CELL_LENGTH) + HALF_CELL_LENGTH);
                    fY += (y-1) * CELL_LENGTH;
                    glBegin(GL_QUADS);
                        glNormal3f(0,-1,0);
                        glTexCoord2f(0.0f, 0.0f); glVertex3f(fX - HALF_PEICE_LENGTH, -0.1f,  fY - HALF_PEICE_LENGTH);	// Bottom Left Of The Texture and Quad
                        glTexCoord2f(1.0f, 0.0f); glVertex3f(fX + HALF_PEICE_LENGTH, -0.1f,  fY - HALF_PEICE_LENGTH);	// Bottom Right Of The Texture and Quad
                        glTexCoord2f(1.0f, 1.0f); glVertex3f(fX + HALF_PEICE_LENGTH, -0.1f,  fY + HALF_PEICE_LENGTH);	// Top Right Of The Texture and Quad
                        glTexCoord2f(0.0f, 1.0f); glVertex3f(fX - HALF_PEICE_LENGTH, -0.1f,  fY + HALF_PEICE_LENGTH);	// Top Left Of The Texture and Quad
                    glEnd();
                }
            }  
        }
    }
    DrawMovingPeice();
}

void CDglCheckers3d::DrawSelectors()
{
    glPushMatrix();
    glTranslatef(-3.5, 0, -3.5);
    if (bGameInProgress & ((cTurn == WHITE & bWhiteIsLocalHuman) | (cTurn == BLACK & bBlackIsLocalHuman)))
	{
    	if (!bTargetSelected)
    	{
    	    if (bPeiceSelected & !bTargetSelected)
    	    {
            	glColor3ub(0, 255, 255); 
            	glPushMatrix();
                glTranslatef(aiSelect[cTurn][0], 0, aiSelect[cTurn][1]);
                glBegin(GL_QUADS);
                    glNormal3f(0,-1,0);
              		glVertex3f(-0.1f, -0.2f,  -0.1f);	// Bottom Left Of The Texture and Quad
              		glVertex3f( 0.1f, -0.2f,  -0.1f);	// Bottom Right Of The Texture and Quad
              		glVertex3f( 0.1f,  -0.2f,  0.1f);	// Top Right Of The Texture and Quad
              		glVertex3f(-0.1f,  -0.2f,  0.1f);	// Top Left Of The Texture and Quad
                glEnd();
                glPopMatrix();
            }    
            
            if (false) // dont show this!
            {
                glColor3ub(255, 255, 0); 
            	glPushMatrix();
                glTranslatef(aiSelect[TARGET][0], 0, aiSelect[TARGET][1]);
                glBegin(GL_QUADS);
                    glNormal3f(0,-1,0);
              		glVertex3f(-0.1f, -0.3f,  -0.1f);	// Bottom Left Of The Texture and Quad
              		glVertex3f( 0.1f, -0.3f,  -0.1f);	// Bottom Right Of The Texture and Quad
              		glVertex3f( 0.1f,  -0.3f,  0.1f);	// Top Right Of The Texture and Quad
              		glVertex3f(-0.1f,  -0.3f,  0.1f);	// Top Left Of The Texture and Quad
                glEnd();
                glPopMatrix();
            }    
        }    
    }
    glPopMatrix();
}    

void CDglCheckers3d::DrawOrthoStuff()
{
    openglWindow.PushOrthoMode();
	if (bDisplayMenu)
	{
    	glEnable(GL_TEXTURE_2D);
    	gameMenu.DrawOgl();
    	//glDisable(GL_TEXTURE_2D);
    }   
    if (bWinner)
    {
        int iMaskId;
        int iId;
        if (cWinner == WHITE)
        {
            iMaskId = dgltextureMaskWhiteWin.GetTextureID();
            iId = dgltextureWhiteWin.GetTextureID();
        }
        else
        {
            iMaskId = dgltextureMaskBlackWin.GetTextureID();
            iId = dgltextureBlackWin.GetTextureID();
        }       
        int iDistanceFromLeft = (SCREEN_WIDTH - WIN_LOGO_WIDTH) / 2;
        glEnable(GL_TEXTURE_2D);
        glColor3ub(255,255,255);
    	glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_DST_COLOR,GL_ZERO);
    	glEnable(GL_BLEND);						
    	glBindTexture(GL_TEXTURE_2D,  iMaskId);
    	glBegin(GL_QUADS);
    		// Display the top left point of the 2D image
    		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, 0);
    		// Display the bottom left point of the 2D image
    		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, 0+WIN_LOGO_HEIGHT);
    		// Display the bottom right point of the 2D image
    		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+WIN_LOGO_WIDTH, 0+WIN_LOGO_HEIGHT);
    		// Display the top right point of the 2D image
    		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+WIN_LOGO_WIDTH, 0);
    	glEnd();
    	glBlendFunc(GL_ONE,GL_ONE);  
    	glBindTexture(GL_TEXTURE_2D,  iId);
    	glBegin(GL_QUADS);
    		// Display the top left point of the 2D image
    		glTexCoord2f(0.0f, 1.0f);	glVertex2f(iDistanceFromLeft, 0);
    		// Display the bottom left point of the 2D image
    		glTexCoord2f(0.0f, 0.0f);	glVertex2f(iDistanceFromLeft, 0+WIN_LOGO_HEIGHT);
    		// Display the bottom right point of the 2D image
    		glTexCoord2f(1.0f, 0.0f);	glVertex2f(iDistanceFromLeft+WIN_LOGO_WIDTH, 0+WIN_LOGO_HEIGHT);
    		// Display the top right point of the 2D image
    		glTexCoord2f(1.0f, 1.0f);	glVertex2f(iDistanceFromLeft+WIN_LOGO_WIDTH, 0);
    	glEnd();
    	glDisable(GL_BLEND);
    	glEnable(GL_DEPTH_TEST);
    	//glDisable(GL_TEXTURE_2D);
    }    
    //draw mouse
    glEnable(GL_TEXTURE_2D);
    glColor3ub(255,255,255);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_DST_COLOR,GL_ZERO);
	glEnable(GL_BLEND);						
	glBindTexture(GL_TEXTURE_2D,  dgltextureMaskMouse.GetTextureID());
	glBegin(GL_QUADS);
		// Display the top left point of the 2D image
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(lMouseX, lMouseY);
		// Display the bottom left point of the 2D image
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(lMouseX, lMouseY+MOUSE_HEIGHT);
		// Display the bottom right point of the 2D image
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(lMouseX+MOUSE_WIDTH, lMouseY+MOUSE_HEIGHT);
		// Display the top right point of the 2D image
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(lMouseX+MOUSE_WIDTH, lMouseY);
	glEnd();
	glBlendFunc(GL_ONE,GL_ONE);  
	glBindTexture(GL_TEXTURE_2D,  dgltextureMouse.GetTextureID());
	glBegin(GL_QUADS);
		// Display the top left point of the 2D image
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(lMouseX, lMouseY);
		// Display the bottom left point of the 2D image
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(lMouseX, lMouseY+MOUSE_HEIGHT);
		// Display the bottom right point of the 2D image
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(lMouseX+MOUSE_WIDTH, lMouseY+MOUSE_HEIGHT);
		// Display the top right point of the 2D image
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(lMouseX+MOUSE_WIDTH, lMouseY);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
    //end draw mouse
    openglWindow.PopOrthoMode();
}    

void CDglCheckers3d::Draw(bool bTestingMouse)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The matrix
    gluLookAt(	0, -11, -10,		0, 0, 0,	0, -1, 0);
    glClearColor(0.4f, 0.4f, 1.2f, 1);
    
    //object selection
    glInitNames();		// This clears the name stack so we always start with 0 names.
    
    if (bTestingMouse)
    {
        glPushMatrix();                     
        glRotatef(fRotation, 0,1,0);
        DrawBoard();
        glPopMatrix();
    }
    else
    {
        
        GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat LightPosition1[]=	{ 0.0f, -8.0f, -10.0f, 1.0f };
        //GLfloat LightPosition1[]=	{ 4.0f, -12.0f, -4.0f, 1.0f };
        GLfloat LightPosition2[]=	{ -4.0f, -12.0f, 4.0f, 1.0f };
        GLfloat LightPosition3[]=	{ 4.0f, -12.0f, 4.0f, 1.0f };
        GLfloat LightPosition4[]=	{ -4.0f, -12.0f, -4.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
        glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
        glLightfv(GL_LIGHT1, GL_POSITION,LightPosition1);	// Position The Light
        glEnable(GL_LIGHT1);	
        /*							// Enable Light One
        //glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
        //glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
        glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);	// Position The Light
        glEnable(GL_LIGHT2);								// Enable Light One
        //glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
        //glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
        glLightfv(GL_LIGHT3, GL_POSITION,LightPosition2);	// Position The Light
        glEnable(GL_LIGHT3);								// Enable Light One
        //glLightfv(GL_LIGHT4, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
        //glLightfv(GL_LIGHT4, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
        glLightfv(GL_LIGHT4, GL_POSITION,LightPosition2);	// Position The Light
        glEnable(GL_LIGHT4);								// Enable Light One
        */
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        
        glPushMatrix();
        glRotatef(fRotation, 0,1,0);
        DrawSelectors();
        DrawPeices();
        DrawBoard();
        glPopMatrix();
        
        glDisable(GL_LIGHTING);
        
        DrawOrthoStuff();
    }
    
    SwapBuffers(openglWindow.GetHDC());    
}    
    

